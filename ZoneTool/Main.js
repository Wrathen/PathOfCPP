// Variables
let allData = {
  "General": { "OutputName": "General", "Data": new ZoneGeneralData() },
  "Background": { "OutputName": "BGData", "Data": new ZoneBackgroundData() },
  "Colliders": { "OutputName": "ColliderData", "Data": [] },
  "Entities": { "OutputName": "EntityData", "Data": [] },
  "SpawnZones": { "OutputName": "SpawnZoneData", "Data": [] },
  "Portals": { "OutputName": "PortalData", "Data": [] }
};
let allTiles = [];
let allColliders = [];
let allEntities = [];
let allSpawnZones = [];
let allPortals = [];
let allObjectArrays = [allTiles, allColliders, allEntities, allSpawnZones, allPortals];

let zoneWidth = 4000;
let zoneHeight = 4000;

let cookingModeEnabled = false;
let gridsEnabled = false;
let gridSizeX = 160;
let gridSizeY = 160;

let portalImg;
let bgImg;
let tileImgs = [];
let currentSelectedTileImg;
let currentSelectedEntity;
let currentSelection = { "Type": SelectionType.None, "Object": null };
let currentZoneInsertType = ZoneInsertType.Collider;

let mouseStartPos = [-1, -1];

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
  }
}

// Main Functions
function createUIElements() {
  UIElements = [];
  UIElements.push(
    createButton("Hide").position(30, 15).mousePressed(() => {
      let areElementsHidden = UIElements[0].elt.innerHTML == "Hide";

      for (let i = 1; i < UIElements.length; ++i) {
        if (areElementsHidden) UIElements[i].hide();
        else UIElements[i].show();
      }
      UIElements[0].elt.innerHTML = areElementsHidden ? "Show" : "Hide";
    }),
    createButton("Import").position(30, 50).mousePressed(importData),
    createButton("Export").position(90, 50).mousePressed(exportData),

    createP("Zone Name").position(30, 70).style('background-color', 'powderblue'),
    createInput("Unnamed Zone").position(30, 105).input(() => { allData["General"]["Data"].name = UIElements[4].elt.value; }),

    createP("Background Path").position(30, 120).style('background-color', 'powderblue'),
    createInput("assets/sprites/nosprite.png").position(30, 155).input(() => {
      allData["Background"]["Data"].bgPath = UIElements[6].elt.value;
      loadImage(UIElements[6].elt.value, (data) => { bgImg = data; });
    }),
    createInput("Add Tiles").position(30, 200),
    createButton("Cook Background").position(30, 240).mousePressed(cookBackground),
  );

  UIElements[7].elt.onchange = e => {
    for (let i = 0; i < e.target.files.length; ++i) {
      let element = e.target.files[i];
      loadImage("assets/Tiles/" + element.name, (data) => { tileImgs.push({ "Name": element.name, "Data": data }); });
    }
  }
  UIElements[7].elt.type = 'file';
  UIElements[7].elt.multiple = true;
}
function importData() {

}
function exportData() {
  let data = {};
  for (const [key, value] of Object.entries(allData)) {
    if (Array.isArray(value["Data"])) {
      data[value["OutputName"]] = [];
      for (let i = 0; i < value["Data"].length; ++i)
        data[value["OutputName"]].push(value["Data"][i].export());
    }
    else
      data[value["OutputName"]] = value["Data"].export();
  }

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
function insertEntity() {
  if (currentAction != ActionType.EntityInsert) return;
  if (!currentSelectedEntity) return;

  // Insert a new entity into the allEntities array.
  let entity = new Entity(currentSelectedEntity.ID, currentSelectedEntity.Type, currentSelectedEntity.Image, getMouseWorldX(), getMouseWorldY());
  allEntities.push(entity);
  allData.Entities.Data.push(new ZoneEntityData(entity.id, entity.type, entity.x, entity.y));
}
function insertZone() {
  // x, y, w, h
  let zoneBounds = [mouseStartPos[0], mouseStartPos[1], getMouseWorldX() - mouseStartPos[0], getMouseWorldY() - mouseStartPos[1]];
  if (zoneBounds[2] == 0 || zoneBounds[3] == 0) return;

  if (currentZoneInsertType == ZoneInsertType.Collider) {
    allColliders.push(new Collider(...zoneBounds));
    allData.Colliders.Data.push(new ZoneColliderData(...zoneBounds));
  }
  else if (currentZoneInsertType == ZoneInsertType.SpawnZone) {
    allSpawnZones.push(new SpawnZone(...zoneBounds));
    allData.SpawnZones.Data.push(new ZoneSpawnZoneData(...zoneBounds));
  }
  else if (currentZoneInsertType == ZoneInsertType.Portal) {
    allPortals.push(new Portal(...zoneBounds));
    allData.Portals.Data.push(new ZonePortalData(...zoneBounds));
  }
}

function deleteTileData(object) { }
function deleteEntityData(object) { deleteData(allData.Entities.Data, object); }
function deleteColliderData(object) { deleteData(allData.Colliders.Data, object); }
function deleteSpawnZoneData(object) { deleteData(allData.SpawnZones.Data, object); }
function deletePortalData(object) { deleteData(allData.Portals.Data, object); }
function deleteData(dataArray, object) {
  for (let i = 0; i < dataArray.length; ++i) {
    let data = dataArray[i];
    if (data.id == object.id) {
      dataArray.splice(i, 1);
      delete object;
      return;
    }
  }

  alert("Error found while deleting EntityData!");
}

function deleteSelection() {
  if (!hasValidSelection()) return;

  for (let i = 0; i < allObjectArrays.length; ++i) {
    let objectArray = allObjectArrays[i];
    for (let j = 0; j < objectArray.length; ++j) {
      let object = objectArray[j];
      if (object.GUID == currentSelection.Object.GUID) {
        objectArray.splice(j, 1);
        object.deleteData();
        delete currentSelection.Object;
        return;
      }
    }
  }
}
function resetSelection() {
  currentSelection = { "Type": SelectionType.None, "Object": null };
}
function trySelectAtMousePosition() {
  resetSelection();

  let mousePos = new Point(getMouseWorldX(), getMouseWorldY());

  for (let i = 0; i < allObjectArrays.length; ++i) {
    let objectArray = allObjectArrays[i];
    for (let j = 0; j < objectArray.length; ++j) {
      let object = objectArray[j];
      let objectRect = new Rect((object.getWorldX() + cameraOffsetScaled[0]) / zoom, (object.getWorldY() + cameraOffsetScaled[1]) / zoom, object.getRenderWidth() / zoom, object.getRenderHeight() / zoom);

      if (mousePos.intersectsRect(objectRect)) {
        currentSelection.Object = object;
        currentSelection.Type = object.objectType;
        return;
      }
    }
  }
  console.log("couldnt find any objects under mouse");
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