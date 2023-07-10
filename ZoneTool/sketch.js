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
let gridsEnabled = true;
let gridSizeX = 160;
let gridSizeY = 160;

let bgImg;
let tileImgs = [];
let currentSelectedTileImg;
let currentSelectedEntity;

let mouseStartPos = [-1, -1];

let cameraOffset = [2000, 2000];

let currentAction = ActionType.Move; 

// Base Functions
function preload() {
  // Load BG image.
  //loadImage('assets/bg.png', (data) => { bgImg = data; });
  
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
  createCanvas(4000, 4000);

  createUIElements();
}
function draw(){
  // Render BG color&image.
  background(17, 15, 20, zoneWidth, zoneHeight);
  if (bgImg) image(bgImg, cameraOffset[0], cameraOffset[1], zoneWidth, zoneHeight);
  
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
function windowResized() {
  //resizeCanvas(windowWidth - 5, windowHeight - 5);
}
function mousePressed() {
  mouseStartPos = [mouseX, mouseY];
}
function mouseDragged() {
  if (currentAction == ActionType.TileInsert) insertTile();
  else if (currentAction == ActionType.Move) {
    cameraOffset[0] += movedX;
    cameraOffset[1] += movedY;
    
    for (let i = 0; i < UIElements.length; ++i)
      UIElements[i].position(UIElements[i].position.x + cameraOffset[0], UIElements[i].position.y + cameraOffset[1]);
  }
}
function mouseReleased() {
  if (currentAction == ActionType.ColliderInsert) insertCollider();
  else if (currentAction == ActionType.EntityInsert) insertEntity();
  mouseStartPos = [-1, -1];
}
function keyPressed() {
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
    image(allTiles[i][2], allTiles[i][0] - cameraOffset[0], allTiles[i][1] - cameraOffset[1], 16, 16);
}
function drawColliders() {
  push();
  noFill();
  stroke(255, 255, 255);
  strokeWeight(3);
  for (let i = 0; i < allColliders.length; ++i)
    rect(allColliders[i][0], allColliders[i][1], allColliders[i][2], allColliders[i][3]);
  pop();
}
function drawPreviewCollider() {
  if (currentAction != ActionType.ColliderInsert) return;
  if (mouseStartPos[0] == -1 && mouseStartPos[1] == -1) return;

  push();
  rect(mouseStartPos[0], mouseStartPos[1], mouseX - mouseStartPos[0], mouseY - mouseStartPos[1])
  pop();
}
function drawGrids() {
  push();
  noFill();
  stroke(0, 0, 0, 60); // give some transparency for better visuality
  for (let i = 0; i < zoneWidth/gridSizeX; ++i) {
    for (let j = 0; j < zoneHeight/gridSizeY; ++j) {
      rect(i * gridSizeX + cameraOffset[0], j * gridSizeY + cameraOffset[1], gridSizeX, gridSizeY);
    }
  }
  pop();
}
function drawEntities() {
  for (let i = 0; i < allEntities.length; ++i)
    image(allEntities[i].Image, allEntities[i].X - 32 - cameraOffset[0], allEntities[i].Y - 32 - cameraOffset[1], 64, 64);
}
function drawMousePosition() {
  push();
  textSize(32);
  fill(0, 188, 30);
  text(parseInt(mouseX - cameraOffset[0]) + "," + parseInt(mouseY - cameraOffset[1]), 30, windowHeight - 30);
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
    loadImage(UIElements[6].elt.value, (data) => { img = data; });
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
  let zoneName = UIElements[4].elt.value;
  saveAs(blob, `Zone_${zoneName}.PZD`);
}
function insertTile() {
  if (mouseButton !== LEFT) return;
  if (!currentSelectedTileImg) return;

  if (gridsEnabled) {
    let gridPos = getGrid(mouseX + cameraOffset[0], mouseY + cameraOffset[1]);
    allTiles.push([gridPos[0] * gridSizeX, gridPos[1] * gridSizeY, currentSelectedTileImg.Data]);
  }
  else allTiles.push([mouseX + cameraOffset[0], mouseY + cameraOffset[1], currentSelectedTileImg.Data]);
}
function insertEntity() {
  if (currentAction != ActionType.EntityInsert) return;
  if (!currentSelectedEntity) return;

  // Insert a new entity into the allEntities array.
  allEntities.push({"X": mouseX + cameraOffset[0], "Y": mouseY + cameraOffset[1], "ID": currentSelectedEntity.ID, "Image": currentSelectedEntity.Image});
  allData.Entities.Data.push(new ZoneEntityData(currentSelectedEntity.ID, currentSelectedEntity.Type, mouseX + cameraOffset[0], mouseY + cameraOffset[1]));
}
function insertCollider() {
  allColliders.push([mouseStartPos[0] - cameraOffset[0], mouseStartPos[1] - cameraOffset[1], mouseX - mouseStartPos[0], mouseY - mouseStartPos[1]]);
  allData.Colliders.Data.push(new ZoneColliderData(mouseStartPos[0], mouseStartPos[1], mouseX - mouseStartPos[0] + cameraOffset[0], mouseY - mouseStartPos[1] + cameraOffset[1]));
}
function cookBackground() {
  cookingModeEnabled = true;
  setTimeout(() => { saveCanvas(`ZoneBG_${allData.General.OutputName}`, 'png'); cookingModeEnabled = false; }, 500);
}

// Utility Functions
function getGrid(x, y) {
  return [(x/gridSizeX)|0, (y/gridSizeY)|0];
}

// Prevents Right Click Menu
window.addEventListener("contextmenu", function(e) {
  e.preventDefault();
  return false;
});

// @todo: 
// - need camera