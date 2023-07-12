// enums
let EntityTypes = [
  {
    "Name": "Merchant",
    "ID": 0,
    "Type": 0,
    "Image": null
  },
  {
    "Name": "Gambler",
    "ID": 1,
    "Type": 1,
    "Image": null
  },
  {
    "Name": "Blacksmith",
    "ID": 2,
    "Type": 2,
    "Image": null
  }
];
const ActionType = {
  "Move": 0,
  "TileInsert": 1,
  "ColliderInsert": 2,
  "EntityInsert": 3
}
// classes
class ZoneGeneralData {
  constructor(ZoneName = "Unnamed Zone") {
    this.name = ZoneName;
  }
  
  export() {
    return {"Name": this.name};
  }
}
class ZoneBackgroundData {
  constructor(bgPath = "assets/sprites/nosprite.png") {
    this.bgPath = bgPath;
  }

  export() {
    return {"Path": this.bgPath};
  }
}
class ZoneColliderData {
  constructor(posX = 0, posY = 0, w = 0, h = 0) {
    this.posX = posX;
    this.posY = posY;
    this.w = w;
    this.h = h;
  }

  export() {
    return {"PosX": this.posX, "PosY": this.posY, "Width": this.w, "Height": this.h};
  }
}
class ZoneEntityData {
  constructor(ID = 0, type = 0, posX = 0, posY = 0) {
    this.ID = ID;
    this.type = type;
    this.posX = posX;
    this.posY = posY;
  }

  export() {
    return {"ID": this.ID, "Type": this.type, "PosX": this.posX, "PosY": this.posY};
  }
}

// Variables
let allData = {
  "General": {"OutputName": "General", "Data": new ZoneGeneralData()},
  "Background": {"OutputName": "BGData", "Data": new ZoneBackgroundData()},
  "Colliders": {"OutputName": "ColliderData", "Data": []},
  "Entities": {"OutputName": "EntityData", "Data": []}
};
let allTiles = [];
let allColliders = [];
let allEntities = [];

let zoneWidth = 4000;
let zoneHeight = 4000;

let cookingModeEnabled = false;
let gridsEnabled = false;
let gridSizeX = 160;
let gridSizeY = 160;

let bgImg;
let tileImgs = [];
let currentSelectedTileImg;
let currentSelectedEntity;

let mouseStartPos = [-1, -1];

let zoom = 1.0;
let cameraOffset = [0, 0];
let cameraOffsetScaled = [cameraOffset[0] * zoom, cameraOffset[1] * zoom];

let currentAction = ActionType.Move; 

// Base Functions
function preload() {
  // Load BG image.
  loadImage('assets/bg1.png', (data) => { bgImg = data; });
  
  // Load a tile for quick-use.
  loadImage('assets/Tiles/Box_1_16x16.png', (data) => {
    tileImgs.push({"Name": "Box_1_16x16.png", "Data": data});
    currentSelectedTileImg = {"Name": "Box_1_16x16.png", "Data": data};
  });

  // Load all Entities' images.
  for (let i = 0; i < EntityTypes.length; ++i)
    loadImage(`assets/Entities/${EntityTypes[i].Name}.png`, (data) => { EntityTypes[i].Image = data; })
}
function setup(){
  createCanvas(zoneWidth, zoneHeight);

  createUIElements();

  disableScrollingInterval = setInterval(disableScrolling, 50);
}
function draw(){
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

    // Render preview collider that we are currently inserting.
    drawPreviewCollider();
      
    // Render all entities.
    drawEntities();

    // Render mouse position at bottom-left.
    drawMousePosition();

    // Render current action.
    drawCurrentAction();
  }
}
function mousePressed() {
  if (cookingModeEnabled) return;
  
  mouseStartPos = [getMouseWorldX(), getMouseWorldY()];
}
function mouseDragged() {
  if (cookingModeEnabled) return;
  
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

  if (currentAction == ActionType.ColliderInsert) insertCollider();
  else if (currentAction == ActionType.EntityInsert) insertEntity();
  mouseStartPos = [-1, -1];
}
function mouseWheel(event) {
  if (cookingModeEnabled) return;

  let zoomDirection = event.deltaY < 0 ? 1 : -1;
  let zoomDelta = zoomDirection * 0.25;
  zoom += zoomDelta;
  if (zoom < 0.25) zoom = 0.25;
  
  //let mouseScreenPosX = windowWidth/2 - mouseX;
  //let mouseScreenPosY = windowHeight/2 - mouseY;

  //cameraOffset[0] = (cameraOffsetScaled[0] - (zoomDirection == 1 ? mouseScreenPosX: 0)) / zoom ;
  //cameraOffset[1] = (cameraOffsetScaled[1] - (zoomDirection == 1 ? mouseScreenPosY: 0)) / zoom;
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

  // ActionType-Independent KeyPresses
  switch(keyCode) {
    // h key, toggle grids
    case 72:
      gridsEnabled = !gridsEnabled;
      break;
    // t key, switch into TileInsert action mode.
    case 84:
      currentAction = ActionType.TileInsert;
      break;
    // c key, switch into ColliderInsert action mode.
    case 67:
      currentAction = ActionType.ColliderInsert;
      break;
    // e key, switch into EntityInsert action mode.
    case 69:
      currentAction = ActionType.EntityInsert;
      break;
    // d key, switch into Move action mode.
    case 68:
      currentAction = ActionType.Move;
      break;
  }
}

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
function drawPreviewCollider() {
  if (currentAction != ActionType.ColliderInsert) return;
  if (mouseStartPos[0] == -1 && mouseStartPos[1] == -1) return;

  rect(mouseStartPos[0] * zoom - cameraOffsetScaled[0], mouseStartPos[1] * zoom - cameraOffsetScaled[1], (getMouseWorldX() - mouseStartPos[0]) * zoom, (getMouseWorldY() - mouseStartPos[1]) * zoom)
}
function drawGrids() {
  push();
  noFill();
  stroke(255, 255, 255, 250); // give some transparency for better visuality
  for (let i = 0; i < zoneWidth/gridSizeX; ++i) {
    for (let j = 0; j < zoneHeight/gridSizeY; ++j) {
      rect(i * gridSizeX * zoom - cameraOffsetScaled[0], j * gridSizeY * zoom - cameraOffsetScaled[1], gridSizeX * zoom, gridSizeY * zoom);
    }
  }
  pop();
}
function drawEntities() {
  for (let i = 0; i < allEntities.length; ++i) {
    let scaledWidth = 64 * zoom;
    let scaledHeight = 64 * zoom;
    image(allEntities[i].Image, allEntities[i].X * zoom - scaledWidth/2 - cameraOffsetScaled[0], allEntities[i].Y * zoom - scaledHeight/2 - cameraOffsetScaled[1], scaledWidth, scaledHeight);
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
  
  let suffix = currentAction == ActionType.EntityInsert ? (currentSelectedEntity ? currentSelectedEntity.Name: ""):
               currentAction == ActionType.TileInsert ? (currentSelectedTileImg ? currentSelectedTileImg.Name: ""): ""; 
  text(`${Object.keys(ActionType)[currentAction]} ${suffix}`, windowWidth/2, windowHeight - 30);
  
  pop();
}

function getMouseScreenX() { return mouseX; }
function getMouseScreenY() { return mouseY; }
function getMouseWorldX() { return (mouseX + cameraOffsetScaled[0]) / zoom; }
function getMouseWorldY() { return (mouseY + cameraOffsetScaled[1]) / zoom; }
function getZoneName() { return UIElements[4].value(); }
//function screenToWorld(pos) { return [pos[0] + cameraOffsetScaled[0], pos[1] + cameraOffsetScaled[1]]; } 

// Main Functions
function createUIElements() {
  UIElements = [];
  UIElements.push(
  createButton("Hide").position(30, 15).mousePressed(() => {
    let areElementsHidden = UIElements[0].elt.innerHTML == "Hide";

    for(let i = 1; i < UIElements.length; ++i) {
      if (areElementsHidden) UIElements[i].hide();
      else UIElements[i].show();
    }
    UIElements[0].elt.innerHTML = areElementsHidden ? "Show": "Hide";
  }),
  createButton("Import").position(30, 50).mousePressed(importData),
  createButton("Export").position(90, 50).mousePressed(exportData),

  createP("Zone Name").position(30, 70).style('background-color', 'powderblue'),
  createInput("Unnamed Zone").position(30, 105).input(() => {allData["General"]["Data"].name = UIElements[4].elt.value;}),

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
      loadImage("assets/Tiles/" + element.name, (data) => { tileImgs.push({"Name": element.name, "Data": data}); });
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

  if (gridsEnabled) {
    let gridPos = getGrid(getMouseWorldX(), getMouseWorldY());
    allTiles.push([gridPos[0] * gridSizeX, gridPos[1] * gridSizeY, currentSelectedTileImg.Data]);
  }
  else allTiles.push([getMouseWorldX(), getMouseWorldY(), currentSelectedTileImg.Data]);
}
function insertEntity() {
  if (currentAction != ActionType.EntityInsert) return;
  if (!currentSelectedEntity) return;

  // Insert a new entity into the allEntities array.
  allEntities.push({"X": getMouseWorldX(), "Y": getMouseWorldY(), "ID": currentSelectedEntity.ID, "Image": currentSelectedEntity.Image});
  allData.Entities.Data.push(new ZoneEntityData(currentSelectedEntity.ID, currentSelectedEntity.Type, getMouseWorldX(), getMouseWorldY()));
}
function insertCollider() {
  allColliders.push([mouseStartPos[0], mouseStartPos[1], getMouseWorldX() - mouseStartPos[0], getMouseWorldY() - mouseStartPos[1]]);
  allData.Colliders.Data.push(new ZoneColliderData(mouseStartPos[0] - cameraOffsetScaled[0], mouseStartPos[1] - cameraOffsetScaled[1], getMouseWorldX() - mouseStartPos[0] - cameraOffsetScaled[0], getMouseWorldY() - mouseStartPos[1] - cameraOffsetScaled[1]));
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

// Utility Functions
function getGrid(x, y) {
  return [(x/gridSizeX)|0, (y/gridSizeY)|0];
}
// Prevents mouse scroll, Press D and switch to Move action and move manually.
function disableScrolling() {
  if (!canvas) return;

  canvas.addEventListener("mousewheel", function (e) {mouseWheel(e); e.preventDefault(); e.stopPropagation(); return false;}, false);
  canvas.addEventListener("DOMMouseScroll", function (e) {mouseWheel(e); e.preventDefault(); e.stopPropagation(); return false;}, false);

  clearInterval(disableScrollingInterval);
}

// Prevents Right Click Menu
window.addEventListener("contextmenu", function(e) {
  e.preventDefault();
  return false;
});