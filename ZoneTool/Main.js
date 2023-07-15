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
let gridsEnabled = false;
let gridSizeX = 160;
let gridSizeY = 160;

let portalImg;
let bgImg;
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
  createCanvas(zoneWidth, zoneHeight);

  createUIElements();

  disableScrollingInterval = setInterval(disableScrolling, 50);
}
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

    // Render zone rectangle that we are currently inserting.
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
  }
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
function insertTile() {
  if (mouseButton !== LEFT) return;
  if (!currentSelectedTileImg) return;

  let mouseWorldPos = [getMouseWorldX(), getMouseWorldY()];
  let pos = [...mouseWorldPos];

  // If we are using grid mode, we should set our X and Y accordingly...
  if (gridsEnabled) {
    let gridPos = getGrid(...mouseWorldPos);
    pos[0] = gridPos[0] * gridSizeX + gridSizeX / 2;
    pos[1] = gridPos[1] * gridSizeY + gridSizeY / 2;
  }

  allTiles.push(new Tile(currentSelectedTileImg.Data, pos[0], pos[1]));
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

function deleteSelection() {
  if (!hasValidSelection()) return;

  for (let i = 0; i < allObjectArrays.length; ++i) {
    let objectArray = allObjectArrays[i];
    for (let j = 0; j < objectArray.length; ++j) {
      let object = objectArray[j];
      if (object.GUID == currentSelection.GUID) {
        objectArray.splice(j, 1);
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
  let worldPos = screenToWorld(new Point(mouseX + selectionDistToOrigin.x, mouseY + selectionDistToOrigin.y));
  currentSelection.x = worldPos.x;
  currentSelection.y = worldPos.y;

  if (currentSelectionMenuBar) moveSelectionMenuBar();
}
function tryAddSelectionMenuBar() {
  resetSelectionMenuBar();

  if (currentSelection.objectType == ObjectType.SpawnZone) {
    currentSelectionMenuBar = [
      createP("Spawn Amount").position(currentSelection.getScreenX(), currentSelection.getScreenY()).style('background-color', 'powderblue'),
      createInput(String(currentSelection.amount))
        .position(currentSelection.getScreenX(), currentSelection.getScreenY())
        .input(() => {
          const data = parseInt(currentSelectionMenuBar[1].elt.value);
          currentSelection.amount = isNaN(data) ? 0 : data;
        }),
      [[0, -15], [100, 0]] // offsets
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