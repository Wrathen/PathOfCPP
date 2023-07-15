// Variables
let allTiles = [];
let allColliders = [];
let allEntities = [];
let allSpawnZones = [];
let allPortals = [];
let allObjectArrays = [allTiles, allColliders, allEntities, allSpawnZones, allPortals];

let data_General = new ZoneGeneralData();
let data_Background = new ZoneBackgroundData();

let zoneWidth = 4000;
let zoneHeight = 4000;

let cookingModeEnabled = false;
let panelElementsHidden = false;
let gridsEnabled = true;
let gridSizeX = 32;
let gridSizeY = 32;

// Spatial Mapping
let spatialMap = new SpatialMap(zoneWidth, zoneHeight, gridSizeX, gridSizeY);

let portalImg;
let bgImg;
let cookedGridImg;
let tileImgs = [];
let currentSelectedTileImg;
let currentSelectedEntity;
let currentSelection = null;
let currentSelectionMenuBar = null;
let currentSelectedInventoryIndex = 0;
let currentZoneInsertType = ZoneInsertType.Collider;

let mouseStartPos = [-1, -1];
let selectionDistToOrigin = [-1, -1];

let zoom = 1.0;
let cameraOffset = [0, 0];
let cameraOffsetScaled = [cameraOffset[0] * zoom, cameraOffset[1] * zoom];

let currentAction = ActionType.Move;

// Base Functions
function preload() {
  // Load BG image.
  loadImage('assets/bg1.png', (data) => { bgImg = data; });

  // Load default Portal image.
  loadImage('assets/portal.png', (data) => { portalImg = data; })

  // Load a tile for quick-use.
  loadImage('assets/Tiles/Box_1_16x16.png', (data) => {
    tileImgs.push({ "Name": "Box_1_16x16.png", "Data": data });
    currentSelectedTileImg = { "Name": "Box_1_16x16.png", "Data": data };
  });

  // Load all Entities' images.
  for (let i = 0; i < EntityTypes.length; ++i)
    loadImage(`assets/Entities/${EntityTypes[i].Name}.png`, (data) => { EntityTypes[i].Image = data; })
}
function setup() {
  // Create the canvas.
  createCanvas(zoneWidth, zoneHeight);

  // Create the UI Elements that are shown on left-side panel.
  createUIElements();

  // Disable Scrolling using Mouse. We have keybind for moving around in map (D).
  disableScrollingInterval = setInterval(disableScrolling, 50);

  // Init Spatial Map
  spatialMap.init();

  // Cook Grid Img so we save ALOT of FPS when gridMode is enabled. HUGE Optimization here.
  cookGridBackground();
}

// Main Functions
function createUIElements() {
  UIElements = [];
  UIElements.push(
    createButton("Hide").position(30, 15).mousePressed(() => {
      for (let i = 1; i < UIElements.length; ++i) {
        if (panelElementsHidden) UIElements[i].show();
        else UIElements[i].hide();
      }
      UIElements[0].elt.innerHTML = panelElementsHidden ? "Hide" : "Show";
      panelElementsHidden = !panelElementsHidden;
    }),
    createButton("Import").position(30, 50),
    createButton("Export").position(90, 50).mousePressed(exportData),

    createP("Zone Name").position(30, 70).style('background-color', 'powderblue'),
    createInput("Unnamed Zone").position(30, 105).input(() => { data_General.name = UIElements[4].elt.value; }),

    createP("Background Path").position(30, 120).style('background-color', 'powderblue'),
    createInput("assets/sprites/nosprite.png").position(30, 155).input(() => {
      data_Background.bgPath = UIElements[6].elt.value;
      loadImage(UIElements[6].elt.value, (data) => { bgImg = data; });
    }),
    createButton("Add Tiles").position(30, 200),
    createButton("Cook Background").position(30, 240).mousePressed(cookBackground),
    createInput("_Hidden_IMPORT_Tiles").style("display", "none"),
    createInput("_Hidden_IMPORT_Data").style("display", "none"),
  );

  // Bind Buttons to Functions so we can call them by .click(), 'cuz p5.js don't allow us.
  UIElements[1].elt.onclick = () => { UIElements[10].elt.click(); };
  UIElements[7].elt.onclick = () => { UIElements[9].elt.click(); };

  // Import Tiles
  UIElements[9].elt.onchange = e => {
    for (let i = 0; i < e.target.files.length; ++i) {
      let element = e.target.files[i];
      loadImage("assets/Tiles/" + element.name, (data) => { tileImgs.push({ "Name": element.name, "Data": data }); });
    }
  }
  UIElements[9].elt.type = 'file';
  UIElements[9].elt.multiple = true;

  // Import Data
  UIElements[10].elt.onchange = e => { if (e.target.files[0]) e.target.files[0].text().then(importData); }
  UIElements[10].elt.type = 'file';
}

function importData(rawData) {
  let data = JSON.parse(rawData);
  data_General = data.General;
  data_Background = data.BGData;

  getUIZoneName().elt.value = data_General.name;
  getUIBackgroundPath().elt.value = data_Background.bgPath;

  currentAction = ActionType.EntityInsert;
  // Import all current objects into the output data.
  for (let i = 0; i < data.EntityData.length; ++i)
    insertEntity(getEntityByID(data.EntityData[i].ID), [data.EntityData[i].PosX, data.EntityData[i].PosY]);
  for (let i = 0; i < data.ColliderData.length; ++i) {
    let d = data.ColliderData[i];
    insertZone(ZoneInsertType.Collider, [d.PosX, d.PosY, d.Width, d.Height]);
  }
  for (let i = 0; i < data.SpawnZoneData.length; ++i) {
    let d = data.SpawnZoneData[i];
    insertZone(ZoneInsertType.SpawnZone, [d.PosX, d.PosY, d.Width, d.Height]);
  }
  for (let i = 0; i < data.PortalData.length; ++i) {
    let d = data.PortalData[i];
    insertZone(ZoneInsertType.Portal, [d.PosX, d.PosY, d.Width, d.Height]);
  }
  currentAction = ActionType.Move;
}
function exportData() {
  // Initialize export data.
  let data = {
    "General": data_General,
    "BGData": data_Background,
    "ColliderData": [],
    "EntityData": [],
    "SpawnZoneData": [],
    "PortalData": []
  };

  // Export all current objects into the output data.
  for (let i = 0; i < allColliders.length; ++i)
    data["ColliderData"].push(allColliders[i].export());
  for (let i = 0; i < allEntities.length; ++i)
    data["EntityData"].push(allEntities[i].export());
  for (let i = 0; i < allSpawnZones.length; ++i)
    data["SpawnZoneData"].push(allSpawnZones[i].export());
  for (let i = 0; i < allPortals.length; ++i)
    data["PortalData"].push(allPortals[i].export());

  // Convert to JSON and save it.
  let JSONConverted = JSON.stringify(data);
  var blob = new Blob([JSONConverted], { type: "text/plain;charset=utf-8" });
  saveAs(blob, `Zone_${getZoneName()}.PZD`);
}

// Main Functions
function insertTile(tileImg, targetPos) {
  if (!tileImg) return;

  // Get Grid&World position
  let gridPos = getGrid(...targetPos);
  let worldPos = [gridPos[0] * gridSizeX + gridSizeX / 2, gridPos[1] * gridSizeY + gridSizeY / 2];

  // Create a tile only if a tile doesn't exist on the target position in the SpatialMap.
  if (!spatialMap.get(worldPos[0], worldPos[1])) {
    let tile = new Tile(currentSelectedTileImg.Data, worldPos[0], worldPos[1]);
    allTiles.push(tile);
    spatialMap.add(tile, tile.x, tile.y);
  }
}
function insertEntity(_entity, _pos) {
  if (currentAction != ActionType.EntityInsert) return;

  let entity = _entity ? _entity : currentSelectedEntity;
  let pos = _pos ? _pos : [getMouseWorldX(), getMouseWorldY()];

  if (!entity) return;

  // Insert a new entity into the allEntities array.
  let spawnedEntity = new Entity(entity.ID, entity.Type, entity.Image, pos[0], pos[1]);
  allEntities.push(spawnedEntity);
}
function insertZone(_zoneType, _zoneBounds) {
  // x, y, w, h
  let zoneType = _zoneType ? _zoneType : currentZoneInsertType;
  let zoneBounds = _zoneBounds ? _zoneBounds : [mouseStartPos[0], mouseStartPos[1], getMouseWorldX() - mouseStartPos[0], getMouseWorldY() - mouseStartPos[1]];

  // width and height can not be lower than 3 units.
  if (Math.abs(zoneBounds[2]) < 3 || Math.abs(zoneBounds[3]) < 3) return;

  // Check if width|height are negative, if so, convert them to positive and adjust x,y instead.
  if (zoneBounds[2] < 0) {
    zoneBounds[0] += zoneBounds[2];
    zoneBounds[2] = -zoneBounds[2];
  }
  if (zoneBounds[3] < 0) {
    zoneBounds[1] += zoneBounds[3];
    zoneBounds[3] = -zoneBounds[3];
  }

  // Create the Zone and push it into their respective array.
  if (zoneType == ZoneInsertType.Collider)
    allColliders.push(new Collider(...zoneBounds));
  else if (zoneType == ZoneInsertType.SpawnZone)
    allSpawnZones.push(new SpawnZone(...zoneBounds));
  else if (zoneType == ZoneInsertType.Portal)
    allPortals.push(new Portal(...zoneBounds));
}

function fillTile(targetPos, tileImg) {
  // If the target position is out of bounds, stop this iteration.
  if (targetPos[0] < 0 || targetPos[0] > spatialMap.mapWidth ||
      targetPos[1] < 0 || targetPos[1] > spatialMap.mapHeight) return;

  // Get the object at targeted position.
  let objectAtTargetPos = spatialMap.get(targetPos[0], targetPos[1]);
  if (objectAtTargetPos || (objectAtTargetPos && !objectAtTargetPos.img)) return;

  insertTile(tileImg, targetPos);
  fillTile([targetPos[0] + spatialMap.cellWidth, targetPos[1]], tileImg); // right
  fillTile([targetPos[0] - spatialMap.cellWidth, targetPos[1]], tileImg); // left
  fillTile([targetPos[0], targetPos[1] - spatialMap.cellHeight], tileImg); // top
  fillTile([targetPos[0], targetPos[1] + spatialMap.cellHeight], tileImg); // bottom
}

function deleteSelection(target = currentSelection) {
  if (!target) return;

  for (let i = 0; i < allObjectArrays.length; ++i) {
    let objectArray = allObjectArrays[i];
    for (let j = 0; j < objectArray.length; ++j) {
      let object = objectArray[j];
      if (object.GUID == target.GUID) {
        objectArray.splice(j, 1);
        object.delete();

        resetSelection();
        resetSelectionMenuBar();
        return;
      }
    }
  }
}
function resetSelection() {
  currentSelection = null;
}
function trySelectAtMousePosition() {
  let mousePos = new Point(getMouseWorldX(), getMouseWorldY());

  for (let i = 0; i < allObjectArrays.length; ++i) {
    let objectArray = allObjectArrays[i];
    for (let j = 0; j < objectArray.length; ++j) {
      let object = objectArray[j];
      let objectRect = new Rect((object.getScreenX() + cameraOffsetScaled[0]) / zoom, (object.getScreenY() + cameraOffsetScaled[1]) / zoom, object.getRenderWidth() / zoom, object.getRenderHeight() / zoom);

      if (mousePos.intersectsRect(objectRect)) {
        if (currentSelection != object)
          resetSelectionMenuBar();

        currentSelection = object;
        currentSelectionStartPos = [mouseX, mouseY];

        selectionDistToOrigin = worldToScreen(object, mouseStartPos);
        return;
      }
    }
  }

  resetSelection();
  resetSelectionMenuBar();
  selectionDistToOrigin = [-1, -1];
}
function tryMoveSelection() {
  // When moving a tile, snap it into a grid position.
  if (currentSelection.objectType == ObjectType.Tile) {
    let gridIndex = getGrid(getMouseWorldX(), getMouseWorldY());
    let mapPos = new Point(gridIndex[0] * spatialMap.cellWidth, gridIndex[1] * spatialMap.cellHeight);
    let newPos = new Point(mapPos.x + currentSelection.w / 2, mapPos.y + currentSelection.h / 2);

    // If the target pos is not occupied, move the current tile to there.
    if (spatialMap.get(newPos.x, newPos.y) == null)
      currentSelection.move(newPos);
    return;
  }

  // Freely move objects around the map.
  let objectClickPosition = new Point(mouseX + selectionDistToOrigin.x, mouseY + selectionDistToOrigin.y);
  newPos = screenToWorld(objectClickPosition);
  currentSelection.move(newPos);

  // If there is an open selection menu bar, move it too.
  if (currentSelectionMenuBar) moveSelectionMenuBar();
}
function tryAddSelectionMenuBar() {
  resetSelectionMenuBar();

  // If the current selection is a SpawnZone, then create an appropriate Menu Bar.
  if (currentSelection.objectType == ObjectType.SpawnZone) {
    currentSelectionMenuBar = [
      createP("Spawn Amount").position(currentSelection.getScreenX(), currentSelection.getScreenY()).style('background-color', 'powderblue'),
      createInput(String(currentSelection.amount))
        .id("selectionMenuBar")
        .position(currentSelection.getScreenX(), currentSelection.getScreenY())
        .input(() => {
          const data = parseInt(currentSelectionMenuBar[1].elt.value);
          currentSelection.amount = isNaN(data) ? 0 : data;
        }),
      [[0, -15], [100, 0]] // offsets
    ];
  }
  // If the current selection is a Portal, then create an appropriate Menu Bar.
  else if (currentSelection.objectType == ObjectType.Portal) {
    currentSelectionMenuBar = [
      createP("Next Zone").position(currentSelection.getScreenX(), currentSelection.getScreenY()).style('background-color', 'powderblue'),
      createInput(String(currentSelection.nextZone))
        .id("selectionMenuBar")
        .position(currentSelection.getScreenX(), currentSelection.getScreenY())
        .size(currentSelection.getRenderWidth() < 60 ? 60 : currentSelection.getRenderWidth() - 20, 15)
        .input(() => { currentSelection.nextZone = currentSelectionMenuBar[1].elt.value; }),
      [[5, -10], [5, 30]] // offsets
    ];
  }

  // Update positions.
  if (currentSelectionMenuBar) moveSelectionMenuBar();
}
function resetSelectionMenuBar() {
  if (!currentSelectionMenuBar) return;

  for (let i = 0; i < currentSelectionMenuBar.length - 1; ++i)
    currentSelectionMenuBar[i].remove();
  currentSelectionMenuBar = null;
}
function moveSelectionMenuBar() {
  let posX = currentSelection.getScreenX();
  let posY = currentSelection.getScreenY();

  for (let i = 0; i < currentSelectionMenuBar.length - 1; ++i) {
    let offset = currentSelectionMenuBar[currentSelectionMenuBar.length - 1][i];
    currentSelectionMenuBar[i].position(posX + offset[0], posY + offset[1]);
  }
}
function cookBackground() {
  cookingModeEnabled = true;
  zoom = 1.0;
  cameraOffsetScaled = [0, 0];
  setTimeout(() => {
    saveCanvas(`ZoneBG_${getZoneName()}`, 'png');
    cookingModeEnabled = false;

    alert("Make sure to update Background Path field on Left Panel UI.");
  }, 500);
}
// Cook the grid background so we don't draw each individual grid on each frame.
function cookGridBackground(refresh = false) {
  // If we receive a refresh boolean to true, then we should re-cook the img. 
  if (cookedGridImg && !refresh) return;

  cookedGridImg = createImage(zoneWidth, zoneHeight);
  cookedGridImg.loadPixels();

  // Insert Grid Rectangles
  for (let i = 0; i < spatialMap.cellAmountX; ++i)
    for (let j = 0; j < spatialMap.cellAmountY; ++j)
      drawRect(cookedGridImg, i * spatialMap.cellWidth, j * spatialMap.cellHeight, spatialMap.cellWidth, spatialMap.cellHeight);

  cookedGridImg.updatePixels();
}