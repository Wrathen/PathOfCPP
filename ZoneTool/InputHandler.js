let initialClickCancelled = false;

function mousePressed() {
    if (cookingModeEnabled) return;
    if (!isUIPanelHidden() ? (mouseX < 250 && mouseY < 300) : (mouseX < 100 && mouseY < 50)) {
        initialClickCancelled = true;
        return;
    }

    if (currentAction == ActionType.Select)
        trySelectAtMousePosition();
    
    mouseStartPos = [getMouseWorldX(), getMouseWorldY()];
}
function mouseDragged() {
    if (cookingModeEnabled) return;
    if (initialClickCancelled) return;
    if (hasValidSelection()) return;

    if (currentAction == ActionType.TileInsert) insertTile();
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
    if (hasValidSelection()) return;

    if (currentAction == ActionType.ZoneInsert) insertZone();
    else if (currentAction == ActionType.EntityInsert) insertEntity();

    initialClickCancelled = false;
    mouseStartPos = [-1, -1];
}
function mouseWheel(event) {
    if (cookingModeEnabled) return;

    let zoomDirection = event.deltaY < 0 ? 1 : -1;
    let zoomDelta = zoomDirection * 0.25;
    zoom += zoomDelta;
    if (zoom < 0.25) zoom = 0.25;

    cameraOffsetScaled = [cameraOffset[0] * zoom, cameraOffset[1] * zoom];
}
function keyPressed() {
    if (cookingModeEnabled) return;

    if (currentAction == ActionType.TileInsert) {
        // alpha 0, random tile selection
        if (keyCode == 48)
            currentSelectedTileImg = tileImgs[(Math.random() * tileImgs.length) | 0];
        // alpha 1-9, switch between slots
        else if (keyCode > 48 && keyCode < 58) {
            let index = keyCode - 49;
            if (tileImgs.length > index) currentSelectedTileImg = tileImgs[index];
        }
    }
    else if (currentAction == ActionType.EntityInsert) {
        if (keyCode > 48 && keyCode < 52) // alpha 1-3
            currentSelectedEntity = EntityTypes[keyCode - 49];
    }
    else if (currentAction == ActionType.ZoneInsert) {
        if (keyCode > 48 && keyCode < 52)
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
            break;
        // z key, switch into ZoneInsert action mode.
        case 90:
            currentAction = ActionType.ZoneInsert;
            resetSelection();
            break;
        // e key, switch into EntityInsert action mode.
        case 69:
            currentAction = ActionType.EntityInsert;
            resetSelection();
            break;
        // d key, switch into Move action mode.
        case 68:
            currentAction = ActionType.Move;
            resetSelection();
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