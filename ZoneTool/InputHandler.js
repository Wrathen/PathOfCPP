let initialClickCancelled = false;

function mousePressed() {
    if (cookingModeEnabled) return;

    // If the current active element is selection menu bar, then we should cancel initial click for this frame.
    // or If there is an active DOM element (it means focused, such as inputfields etc...) rather than then don't do anything.
    if (document.activeElement.id == "selectionMenuBar" || document.activeElement != document.body) {
        initialClickCancelled = true;
        return;
    }

    // Try to cancel click if it's near the UI Panel on left-side.
    if (!isUIPanelHidden() ? (mouseX < 250) : (mouseX < 100 && mouseY < 50)) {
        initialClickCancelled = true;
        return;
    }

    // Set-up mouse start position for this action.
    mouseStartPos = [getMouseWorldX(), getMouseWorldY()];

    // If the current action is Select, then try to select at mouse position.
    if (currentAction == ActionType.Select) {
        trySelectAtMousePosition();

        // Try to open menu bar if we currently have a selection and it's eligible for a menu.
        if (mouseButton == RIGHT) {
            if (!hasValidSelection()) return;

            tryAddSelectionMenuBar();
            initialClickCancelled = true;
        }
    }
    else if (currentAction == ActionType.TileInsert) {
        if (mouseButton == LEFT) {
            // If Left CTRL is held, fill the entire empty space or override the target tiles with specified tile image.
            if (keyIsDown(17)) {
                fillTile(mouseStartPos, currentSelectedTileImg, spatialMap.get(...mouseStartPos));
                return;
            }

            insertTile(currentSelectedTileImg, mouseStartPos);
        }
        else if (mouseButton == CENTER) pickTile(spatialMap.get(...mouseStartPos));
        else {
            // If Left CTRL is held, delete entire connected same-type of tiles.
            if (keyIsDown(17)) {
                fillTile(mouseStartPos, null, spatialMap.get(...mouseStartPos));
                return;
            }
            deleteSelection(spatialMap.get(...mouseStartPos));
        }
    }
}
function mouseDragged() {
    if (cookingModeEnabled) return;
    if (initialClickCancelled) return;

    if (hasValidSelection()) {
        tryMoveSelection();
        return;
    }

    // Insert Tiles on Mouse Drag.
    if (currentAction == ActionType.TileInsert) {
        if (mouseButton == LEFT) {
            let targetPos = [getMouseWorldX(), getMouseWorldY()];

            // If Left shift is pressed, we should use a trick most programs use that you draw in a straight line.
            if (keyIsDown(16)) {
                let xDiff = Math.abs(targetPos[0] - mouseStartPos[0]);
                let yDiff = Math.abs(targetPos[1] - mouseStartPos[1]);

                if (xDiff > yDiff) targetPos[1] = mouseStartPos[1];
                else targetPos[0] = mouseStartPos[0];
            }

            insertTile(currentSelectedTileImg, targetPos);
        }
        else if (mouseButton == RIGHT) deleteSelection(spatialMap.get(...getMouseWorld()));
    }
    else if (currentAction == ActionType.Move) {
        cameraOffset[0] -= movedX;
        cameraOffset[1] -= movedY;
        cameraOffsetScaled = [cameraOffset[0] * zoom, cameraOffset[1] * zoom];

        for (let i = 0; i < UIElements.length; ++i)
            UIElements[i].position(UIElements[i].position.x + cameraOffsetScaled[0], UIElements[i].position.y + cameraOffsetScaled[1]);
    }
}
function mouseReleased() {
    if (cookingModeEnabled) return;

    if (!hasValidSelection()) {
        if (currentAction == ActionType.ZoneInsert) insertZone();
        else if (currentAction == ActionType.EntityInsert) insertEntity();
    }

    initialClickCancelled = false;
    mouseStartPos = [-1, -1];
    selectionDistToOrigin = [-1, -1];
}
function mouseWheel(event) {
    if (cookingModeEnabled) return;

    // If there is an active DOM element (it means focused, such as inputfields etc...) then don't do anything.
    if (document.activeElement != document.body) return;

    // This function gets called by two events. MouseWheel and DOMMouseWheel. Ignore DOMMouseWheel cuz it is problematic on some browsers.
    if (event.deltaY === undefined) return;

    // CLose selection menu bar if it's open.
    resetSelectionMenuBar();

    // Do Math :^)
    let zoomDirection = event.deltaY < 0 ? 1 : -1;
    let zoomDelta = zoomDirection * 0.25;
    zoom += zoomDelta;
    if (zoom < 0.25) zoom = 0.25;

    cameraOffsetScaled = [cameraOffset[0] * zoom, cameraOffset[1] * zoom];
}
function keyPressed() {
    if (cookingModeEnabled) return;

    // If there is an active DOM element (it means focused, such as inputfields etc...) then don't do anything.
    if (document.activeElement != document.body) return;

    // Inventory Slot Index, alpha 1-9
    if (keyCode >= 48 && keyCode < 58) {
        // alpha 0, randomizes arrays
        if (keyCode == 48) {
            shuffleArray(tileImgs);
            shuffleArray(EntityTypes);
        }

        currentSelectedInventoryIndex = keyCode != 48 ? keyCode - 49 : currentSelectedInventoryIndex;

        currentSelectedTileImg = tileImgs[currentSelectedInventoryIndex];
        currentSelectedEntity = EntityTypes[keyCode - 49];
        currentZoneInsertType = keyCode - 49;
    }

    // ActionType-Independent KeyPresses
    switch (keyCode) {
        // delete key, deletes current selection (can be entity, portalZones, colliders etc...).
        case 46:
            deleteSelection();
            break;
        // esc key, resets current selection.
        case 27:
            resetSelection();
            resetSelectionMenuBar();
            break;
        // h key, toggle grids
        case 72:
            gridsEnabled = !gridsEnabled;
            break;
        // s key, switch into Select action mode.
        case 83:
            currentAction = ActionType.Select;
            break;
        // t key, switch into TileInsert action mode.
        case 84:
            currentAction = ActionType.TileInsert;
            resetSelection();
            resetSelectionMenuBar();
            break;
        // z key, switch into ZoneInsert action mode.
        case 90:
            currentAction = ActionType.ZoneInsert;
            resetSelection();
            resetSelectionMenuBar();
            break;
        // e key, switch into EntityInsert action mode.
        case 69:
            currentAction = ActionType.EntityInsert;
            resetSelection();
            resetSelectionMenuBar();
            break;
        // d key, switch into Move action mode.
        case 68:
            currentAction = ActionType.Move;
            resetSelection();
            resetSelectionMenuBar();
            break;
    }
}

// Prevents mouse scroll, Press D and switch to Move action and move manually.
function disableScrolling() {
    if (!canvas) return;

    canvas.addEventListener("mousewheel", function (e) { mouseWheel(e); e.preventDefault(); e.stopPropagation(); return false; }, false);
    canvas.addEventListener("DOMMouseScroll", function (e) { mouseWheel(e); e.preventDefault(); e.stopPropagation(); return false; }, false);

    clearInterval(disableScrollingInterval);
}

// Prevents Right Click Menu
window.addEventListener("contextmenu", function (e) {
    e.preventDefault();
    return false;
});
