// Render Functions
function drawTiles() {
    for (let i = 0; i < allTiles.length; ++i) {
        let t = allTiles[i];
        image(t.img, t.getWorldX(), t.getWorldY(), t.getRenderWidth(), t.getRenderHeight());
    }
}
function drawColliders() {
    push();
    noFill();
    stroke(255, 255, 255);
    strokeWeight(3);
    for (let i = 0; i < allColliders.length; ++i) {
        let c = allColliders[i];
        rect(c.getWorldX(), c.getWorldY(), c.getRenderWidth(), c.getRenderHeight());
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
        rect(sz.getWorldX(), sz.getWorldY(), sz.getRenderWidth(), sz.getRenderHeight());
    }
    pop();
}
function drawPortals() {
    for (let i = 0; i < allPortals.length; ++i) {
        let p = allPortals[i];
        image(portalImg, p.getWorldX(), p.getWorldY(), p.getRenderWidth(), p.getRenderHeight());
    }
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
    push();
    noFill();
    stroke(255, 255, 255, 250); // give some transparency for better visuality
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
        image(e.img, e.getWorldX(), e.getWorldY(), e.getRenderWidth(), e.getRenderHeight());
    }
}
function drawMousePosition() {
    push();
    textSize(32);
    fill(0, 188, 30);
    text("MousePosUnscaled: " + parseInt(mouseX + cameraOffset[0]) + "," + parseInt(mouseY + cameraOffset[1]), 30, windowHeight);
    text("MousePos: " + parseInt(getMouseWorldX()) + "," + parseInt(getMouseWorldY()), 30, windowHeight - 30);
    text("CamOffset: " + parseInt(cameraOffsetScaled[0]) + "," + parseInt(cameraOffsetScaled[1]), 30, windowHeight - 65);
    text("MouseStartPos: " + parseInt(mouseStartPos[0]) + "," + parseInt(mouseStartPos[1]), 30, windowHeight - 100);
    text("Zoom: " + parseFloat(zoom), 30, windowHeight - 135);
    pop();
}
function drawCurrentAction() {
    push();
    textSize(32);
    textAlign(CENTER);
    fill(0, 188, 30);

    let suffix = currentAction == ActionType.EntityInsert ? (currentSelectedEntity ? currentSelectedEntity.Name : "") :
        currentAction == ActionType.TileInsert ? (currentSelectedTileImg ? currentSelectedTileImg.Name : "") :
            currentAction == ActionType.ZoneInsert ? Object.keys(ZoneInsertType)[currentZoneInsertType] : "";
    text(`${Object.keys(ActionType)[currentAction]} ${suffix}`, windowWidth / 2, windowHeight - 30);

    pop();
}
function drawSelectionBounds() {
    let mousePos = new Point(getMouseWorldX(), getMouseWorldY());

    rect((mousePos.x - 8) * zoom - cameraOffsetScaled[0], (mousePos.y - 8) * zoom - cameraOffsetScaled[1], 16 * zoom, 16 * zoom);
    if (!hasValidSelection()) return;

    let obj = currentSelection.Object;

    push();
    fill(0, 126, 0, 45);
    rect(obj.getWorldX(), obj.getWorldY(), obj.getRenderWidth(), obj.getRenderHeight());
    pop();
}