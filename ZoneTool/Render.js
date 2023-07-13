// Render Functions
function drawTiles() {
    for (let i = 0; i < allTiles.length; ++i)
        image(allTiles[i][2], allTiles[i][0] * zoom - cameraOffsetScaled[0], allTiles[i][1] * zoom - cameraOffsetScaled[1], 16 * zoom, 16 * zoom);
}
function drawColliders() {
    push();
    noFill();
    stroke(255, 255, 255);
    strokeWeight(3);
    for (let i = 0; i < allColliders.length; ++i)
        rect(allColliders[i][0] * zoom - cameraOffsetScaled[0], allColliders[i][1] * zoom - cameraOffsetScaled[1], allColliders[i][2] * zoom, allColliders[i][3] * zoom);
    pop();
}
function drawSpawnZones() {
    push();
    stroke(255, 122, 100);
    fill(0, 0, 200, 100);
    strokeWeight(3);
    for (let i = 0; i < allSpawnZones.length; ++i)
        rect(allSpawnZones[i][0] * zoom - cameraOffsetScaled[0], allSpawnZones[i][1] * zoom - cameraOffsetScaled[1], allSpawnZones[i][2] * zoom, allSpawnZones[i][3] * zoom);
    pop();
}
function drawPortals() {
    for (let i = 0; i < allPortals.length; ++i)
        image(portalImg, allPortals[i][0] * zoom - cameraOffsetScaled[0], allPortals[i][1] * zoom - cameraOffsetScaled[1], allPortals[i][2] * zoom, allPortals[i][3] * zoom);
}
function drawPreviewZone() {
    if (currentAction != ActionType.ZoneInsert) return;
    if (mouseStartPos[0] == -1 && mouseStartPos[1] == -1) return;

    let zoneBounds = [mouseStartPos[0] * zoom - cameraOffsetScaled[0],
            mouseStartPos[1] * zoom - cameraOffsetScaled[1],
            (getMouseWorldX() - mouseStartPos[0]) * zoom,
            (getMouseWorldY() - mouseStartPos[1]) * zoom];

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
        let scaledWidth = 64 * zoom;
        let scaledHeight = 64 * zoom;
        image(allEntities[i].Image, allEntities[i].X * zoom - scaledWidth / 2 - cameraOffsetScaled[0], allEntities[i].Y * zoom - scaledHeight / 2 - cameraOffsetScaled[1], scaledWidth, scaledHeight);
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