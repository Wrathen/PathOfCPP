// enums
const EntityType = {
  "Merchant": 0,
  "Gambler": 1,
  "Blacksmith": 2
}
const ActionType = {
  "ColliderInsert": 0,
  "EntityInsert": 1
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
  "Colliders": {"OutputName": "ColliderData", "Data": [new ZoneColliderData(339.466, 145.222, 35, 40), new ZoneColliderData(4339.466, -645.222, 55, 140)]},
  "Entities": {"OutputName": "EntityData", "Data": [new ZoneEntityData(1, 4, -155.33, -3295.329), new ZoneEntityData(2, 1, 5145.33, 315.329)]}
};
let allTiles = [];


// Main Functions
function CreateUIElements() {
  UIElements = [];
  UIElements.push(createButton("Hide").position(30, 15).mousePressed(() => {
    let areElementsHidden = UIElements[0].elt.innerHTML == "Hide";

    for(let i = 1; i < UIElements.length; ++i) {
      if (areElementsHidden) UIElements[i].hide();
      else UIElements[i].show();
    }
    UIElements[0].elt.innerHTML = areElementsHidden ? "Show": "Hide";
  }),
  createButton("Import").position(30, 50).mousePressed(ImportData),
  createButton("Export").position(90, 50).mousePressed(ExportData),

  createP("Zone Name").position(30, 70).style('background-color', 'powderblue'),
  createInput("Unnamed Zone").position(30, 105).input(() => {allData["General"]["Data"].name = UIElements[4].elt.value;}),

  createP("Background Path").position(30, 120).style('background-color', 'powderblue'),
  createInput("assets/sprites/nosprite.png").position(30, 155).input(() => {
    allData["Background"]["Data"].bgPath = UIElements[6].elt.value;
    loadImage(UIElements[6].elt.value, (data) => { img = data; });
  }),
  );
}
function ShowMousePosition() {
  push();
  textSize(32);
  fill(0, 188, 30);
  text(parseInt(mouseX) + "," + parseInt(mouseY), 30, windowHeight - 30);
  pop();
}
function ImportData() {

}
function ExportData() {
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

// Base Functions
function setup(){
  createCanvas(windowWidth - 5, windowHeight - 5);

  CreateUIElements();
}
function draw(){
  background(127, 30, 40, windowWidth, windowHeight);
  image(img, 0, 0, windowWidth, windowHeight);
  
  for (let i = 0; i < allTiles.length; ++i)
    image(allTiles[i][2], allTiles[i][0], allTiles[i][1], 16, 16);
    
  ShowMousePosition();
}
function windowResized() {
  resizeCanvas(windowWidth - 5, windowHeight - 5);
}

function mouseDragged() {
  if (mouseButton === LEFT && currentSelectedTileImg)
    allTiles.push([mouseX, mouseY, currentSelectedTileImg]);
}
function keyPressed() {
  // alpha 1-9, switch between slots
  if (keyCode > 48 && keyCode < 58) {
    let index = keyCode - 49;
    if (tileImgs.length > index) currentSelectedTileImg = tileImgs[index];
  }

  // alpha 0 random tile
  if (keyCode == 48)
    currentSelectedTileImg = tileImgs[(Math.random() * tileImgs.length) | 0];
}


// Prevents Right Click Menu
window.addEventListener("contextmenu", function(e) {
  e.preventDefault();
  return false;
});

let img;
let tileImgs = [];
let currentSelectedTileImg;
let input;
function preload() {
  loadImage('assets/bg.png', (data) => { img = data; });
  input = createInput("Add Tiles");
  input.elt.type = 'file';
  input.elt.multiple = true;
  input.elt.onchange = e => {
    for (let i = 0; i < e.target.files.length; ++i) {
      let element = e.target.files[i];
      loadImage("assets/Tiles/" + element.name, (data) => { tileImgs.push(data); });
    }
  }
}