// Render Functions
function draw() {
    // Render BG color&image.
    background(17, 15, 20, zoneWidth, zoneHeight);
    if (bgImg) image(bgImg, -cameraOffsetScaled[0], -cameraOffsetScaled[1], zoneWidth * zoom, zoneHeight * zoom);

    // Render all drawn images.
    drawTiles();

    if (!cookingModeEnabled) {
        // Render Preview Grids.
        if (gridsEnabled) drawGrids();

        // Render all colliders.
        drawColliders();

        // Render all spawn zones.
        drawSpawnZones();

        // Render all portals.
        drawPortals();

        // Render all entities.
        drawEntities();

        // Render preview of tile that we currently selected.
        drawPreviewTile();

        // Render preview of zone rectangle that we currently selected.
        drawPreviewZone();

        // Render current selection object's bounds
        drawSelectionBounds();

        // Render mouse position at bottom-left.
        drawMousePosition();

        // Render current action.
        drawCurrentAction();

        // Render UI Panel background
        drawUIPanelBackground();

        // Render Inventory
        drawInventory();

        // Render FPS
        drawFPS();
    }
}
function drawTiles() {
    for (let i = 0; i < allTiles.length; ++i) {
        let t = allTiles[i];
        image(t.img, t.getScreenX(), t.getScreenY(), t.getRenderWidth(), t.getRenderHeight());
    }
}
function drawColliders() {
    push();
    noFill();
    stroke(255, 255, 255);
    strokeWeight(3);
    for (let i = 0; i < allColliders.length; ++i) {
        let c = allColliders[i];
        rect(c.getScreenX(), c.getScreenY(), c.getRenderWidth(), c.getRenderHeight());
    }
    pop();
}
function drawSpawnZones() {
    push();
    stroke(255, 122, 100);
    fill(0, 0, 200, 100);
    strokeWeight(3);
    for (let i = 0; i < allSpawnZones.length; ++i) {
        let sz = allSpawnZones[i];
        rect(sz.getScreenX(), sz.getScreenY(), sz.getRenderWidth(), sz.getRenderHeight());
    }
    pop();
}
function drawPortals() {
    for (let i = 0; i < allPortals.length; ++i) {
        let p = allPortals[i];
        image(portalImg, p.getScreenX(), p.getScreenY(), p.getRenderWidth(), p.getRenderHeight());
    }
}
function drawPreviewTile() {
    if (currentAction != ActionType.TileInsert) return;
    if (!currentSelectedTileImg) return;

    push();
    let mouseWorldPos = [getMouseWorldX(), getMouseWorldY()];
    let pos = [...mouseWorldPos];

    // Tiles always use Grid Positions.
    let gridPos = getGrid(...mouseWorldPos);
    pos[0] = gridPos[0] * gridSizeX + gridSizeX / 2;
    pos[1] = gridPos[1] * gridSizeY + gridSizeY / 2;

    // Apply Alpha.
    tint(255, 100);

    let t = new Tile(currentSelectedTileImg.Data, pos[0], pos[1]);
    image(t.img, t.getScreenX(), t.getScreenY(), t.getRenderWidth(), t.getRenderHeight());
    pop();
}
function drawPreviewZone() {
    if (currentAction != ActionType.ZoneInsert) return;
    if (mouseStartPos[0] == -1 && mouseStartPos[1] == -1) return;

    let zoneBounds = [mouseStartPos[0] * zoom - cameraOffsetScaled[0],
    mouseStartPos[1] * zoom - cameraOffsetScaled[1],
    (getMouseWorldX() - mouseStartPos[0]) * zoom,
    (getMouseWorldY() - mouseStartPos[1]) * zoom];

    // Colorize it for different insert types.
    {
        push();
        if (currentZoneInsertType == ZoneInsertType.SpawnZone) {
            stroke(255, 122, 100);
            fill(0, 0, 200, 100);
            strokeWeight(3);
        }
        else if (currentZoneInsertType == ZoneInsertType.Portal) {
            // if width or height is 0, image function results in a bad shape, so we just increase w & h by 1.
            ++zoneBounds[2];
            ++zoneBounds[3];
            image(portalImg, ...zoneBounds);
            pop();
            return;
        }
        rect(...zoneBounds);
        pop();
    }
}
function drawGrids() {
    if (cookedGridImg) {
        image(cookedGridImg, -cameraOffsetScaled[0], -cameraOffsetScaled[1], zoneWidth * zoom, zoneHeight * zoom);
        return;
    }

    push();
    noFill();
    stroke(255, 255, 255, 60); // give some transparency for better visuality
    for (let i = 0; i < zoneWidth / gridSizeX; ++i) {
        for (let j = 0; j < zoneHeight / gridSizeY; ++j) {
            rect(i * gridSizeX * zoom - cameraOffsetScaled[0], j * gridSizeY * zoom - cameraOffsetScaled[1], gridSizeX * zoom, gridSizeY * zoom);
        }
    }
    pop();
}
function drawEntities() {
    for (let i = 0; i < allEntities.length; ++i) {
        let e = allEntities[i];
        image(e.img, e.getScreenX(), e.getScreenY(), e.getRenderWidth(), e.getRenderHeight());
    }
}
function drawMousePosition() {
    push();
    textSize(18);
    stroke(0, 0, 0);
    strokeWeight(2);
    fill(0, 188, 30);

    // Keybinds
    {
        push();
        fill(255, 255, 255);
        stroke(0, 0, 0);
        strokeWeight(2);
        text("Keybinds", 10, windowHeight - 225);
        pop();
        text("0-9, D, H, S, Z, T, E, Del, Esc", 10, windowHeight - 205);
        text("LMB, RMB, MouseWheel", 10, windowHeight - 185);
    }

    // Debug Texts
    text("Zoom: " + parseFloat(zoom), 10, windowHeight - 145);
    text("MouseStartPos: " + parseInt(mouseStartPos[0]) + "," + parseInt(mouseStartPos[1]), 10, windowHeight - 110);
    text("CamOffset: " + parseInt(cameraOffsetScaled[0]) + "," + parseInt(cameraOffsetScaled[1]), 10, windowHeight - 75);
    text("MouseWorldPos: " + parseInt(getMouseWorldX()) + "," + parseInt(getMouseWorldY()), 10, windowHeight - 40);
    text("MouseScreenPos: " + parseInt(mouseX) + "," + parseInt(mouseY), 10, windowHeight - 10);
    pop();
}
function drawCurrentAction() {
    push();
    textSize(42);
    textAlign(CENTER);
    fill(117, 117, 233);
    strokeWeight(2);
    stroke(0, 0, 0);

    let suffix = currentAction == ActionType.EntityInsert ? (currentSelectedEntity ? currentSelectedEntity.Name : "") :
        currentAction == ActionType.TileInsert ? (currentSelectedTileImg ? currentSelectedTileImg.Name : "") :
            currentAction == ActionType.ZoneInsert ? Object.keys(ZoneInsertType)[currentZoneInsertType] : "";
    text(`${Object.keys(ActionType)[currentAction]} ${suffix}`, windowWidth / 2, windowHeight - 70);

    pop();
}
function drawSelectionBounds() {
    if (!hasValidSelection()) return;

    push();
    fill(0, 126, 0, 45);
    rect(currentSelection.getScreenX(), currentSelection.getScreenY(), currentSelection.getRenderWidth(), currentSelection.getRenderHeight());
    pop();
}
function drawUIPanelBackground() {
    let boundaries = panelElementsHidden ? [2, 2, 110, 50] : [2, 2, 250, windowHeight];
    push();
    fill(200, 200, 200, 60);
    rect(...boundaries);
    pop();
}
function drawInventory() {
    push();
    let spacing = 37;
    let size = 32;
    let offset = windowWidth / 2 - 4.5 * size;
    let itemOffsetPixel = 4;

    // Draw Item Slots
    for (let i = 0; i < 9; ++i)
        rect(i * spacing + offset - size / 2, windowHeight - 50, size, size);

    // Draw Items
    if (currentAction == ActionType.Move || currentAction == ActionType.Select) {
        for (let i = 0; i < 9; ++i) {
            fill(0, 0, 0);
            rect(i * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);
        }
    }
    else if (currentAction == ActionType.TileInsert) {
        for (let i = 0; i < tileImgs.length && i < 9; ++i) {
            fill(0, 0, 0);
            image(tileImgs[i].Data, i * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);
        }
    }
    else if (currentAction == ActionType.EntityInsert) {
        for (let i = 0; i < EntityTypes.length && i < 9; ++i) {
            fill(0, 0, 0);
            image(EntityTypes[i].Image, i * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);
        }
    }
    else if (currentAction == ActionType.ZoneInsert) {
        // Collider
        rect(0 * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);

        // SpawnZone
        stroke(255, 122, 100);
        fill(0, 0, 200, 100);
        strokeWeight(3);
        rect(1 * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);

        // Portal
        image(portalImg, 2 * spacing + offset - size / 2 + itemOffsetPixel / 2, windowHeight - 50 + itemOffsetPixel / 2, size - itemOffsetPixel, size - itemOffsetPixel);
    }

    // Draw outline for current selection
    noFill();
    stroke(0, 255, 0);
    strokeWeight(2);
    rect(currentSelectedInventoryIndex * spacing + offset - size / 2 - 2, windowHeight - 50 - 2, size + 4, size + 4);
    pop();
}
function drawFPS() {
    push();
    textSize(48);
    textAlign(RIGHT);
    stroke(255, 255, 255);
    strokeWeight(3);
    text(`FPS: ${parseInt(frameRate())}`, windowWidth - 30, 40);
    pop();
}

// Image Manipulations
function drawLine(img, x1, y1, x2, y2, _color = color(255, 255, 255, 60)) {
    for (let i = x1; i <= x2; ++i)
        for (let j = y1; j <= y2; ++j)
            img.set(i, j, _color);
}
function drawRect(img, x, y, w, h, _color = color(255, 255, 255, 60)) {
    drawLine(img, x, y, x + w, y + 1, _color); // top
    drawLine(img, x, y + h - 1, x + w, y + h, _color); // bottom
    drawLine(img, x, y, x + 1, y + h, _color); // left
    drawLine(img, x + w - 1, y, x + w, y + h, _color); // right
}