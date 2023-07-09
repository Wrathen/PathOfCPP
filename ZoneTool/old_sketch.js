var selecting = false;
var drawing = false;
var canDraw = true;
var resizing = false;
var resizingWall;
var dragging;
var draggingOffset;
var currentWallSpecs;
var exportButton;
var animateButton;
var stopButton;
var gameWidthInput;
var gameHeightInput;
var isAnimating = false;
var img_bg;

var mouseLastX;
var mouseLastY;
var walls = [];
var animatedWalls = [];

var gameWidth = 0;
var gameHeight = 0;

function preload() {
  //img_bg = loadImage("bg.png");
}
function setup() {
  createCanvas(windowWidth - 5, windowHeight - 5);
  exportButton = createButton("Export").position(30, 50);
  exportButton.mousePressed(exportMap);
  animateButton = createButton("Animate").position(30, 80);
  animateButton.mousePressed(startAnimation);
  stopButton = createButton("Stop").position(100, 80);
  stopButton.mousePressed(stopAnimation);

  gameWidthInput = createInput("3120").position(30, 15).size(40, 20);
  gameHeightInput = createInput("1080").position(90, 15).size(40, 20);

  gameWidthInput.elt.onchange = () => {gameWidth = parseInt(gameWidthInput.value());};
  gameHeightInput.elt.onchange = () => {gameHeight = parseInt(gameHeightInput.value());};

  gameWidth = 3120;
  gameHeight = 1080;
}
function startAnimation() {
  if (isAnimating) return;
  isAnimating = true;

  for (let i = 0; i < walls.length; i++)
    walls[i].isAlpha = true,
    new Wall(walls[i].x, walls[i].y, walls[i].w, walls[i].h, walls[i].hspd, walls[i].vspd, false, true);
}
function stopAnimation() {
  isAnimating = false;
  animatedWalls = [];

  for (let i = 0; i < walls.length; i++)
    walls[i].isAlpha = false;
}
function draw() {
  background(0, 0, 0, windowWidth, windowHeight);
  //image(img_bg, 0, 0, gameWidth, gameHeight);

  if (isAnimating) {
    for (let i = 0; i < animatedWalls.length; i++)
      walls[i].draw(),
      animatedWalls[i].draw(),
      animatedWalls[i].move();

    push();
    textSize(32);
    fill(255, 56, 44);
    text(parseInt(mouseX) + "," + parseInt(mouseY), 30, windowHeight - 30);
    pop();
    return;
  }

  if (!resizing) document.documentElement.style.cursor = "default";

  let mouseHit = getWall(new Point(mouseX, mouseY));

  if (mouseHit && !resizing) { // Resizing
    if (mouseX + 10 > mouseHit.x + mouseHit.w) {
      if (mouseY + 10 > mouseHit.y + mouseHit.h)
        document.documentElement.style.cursor = "se-resize";
      else if (mouseY - 10 < mouseHit.y)
        document.documentElement.style.cursor = "ne-resize";
      else
        document.documentElement.style.cursor = "e-resize";
    }
    else if (mouseX - 10 < mouseHit.x) {
      if (mouseY + 10 > mouseHit.y + mouseHit.h)
        document.documentElement.style.cursor = "sw-resize";
      else if (mouseY - 10 < mouseHit.y)
        document.documentElement.style.cursor = "nw-resize";
      else
        document.documentElement.style.cursor = "w-resize";
    }
    else if (mouseY - 10 < mouseHit.y) {
      document.documentElement.style.cursor = "n-resize";
    }
    else if (mouseY + 10 > mouseHit.y + mouseHit.h)
      document.documentElement.style.cursor = "s-resize";

    if (!resizing && document.documentElement.style.cursor != "default")
      resizingWall = mouseHit;
  }

  if (dragging) {
    dragging.x = mouseX - draggingOffset.x;
    dragging.y = mouseY - draggingOffset.y;
  }

  for (let i = 0; i < walls.length; i++)
    walls[i].draw();

  if (drawing) {
    push();
    fill(185);
    rect(mouseLastX, mouseLastY, mouseX - mouseLastX, mouseY - mouseLastY);
    pop();
  }

  if (currentWallSpecs)
    currentWallSpecs.draw();

  push();
  fill(255);
  rect(mouseX - 6, mouseY - 6, 12, 12);
  pop();

  push();
  textSize(32);
  fill(255, 56, 44);
  text(parseInt(mouseX) + "," + parseInt(mouseY), 30, windowHeight - 30);
  pop();
}
function windowResized() {
  resizeCanvas(windowWidth - 5, windowHeight - 5);
}
function getWall(p) {
  for (let i = walls.length - 1; i > -1; i--)
    if (CollisionPointRect(p, walls[i]))
      return walls[i];

  return null;
}
function mousePressed() {
  if (document.documentElement.style.cursor != "default") {
    resizing = true;
    return;
  }
  
  // Wall Specs
  let mouseHit = getWall(new Point(mouseX, mouseY));
  if (mouseButton === RIGHT && mouseHit) {
      if (currentWallSpecs) currentWallSpecs.remove();

      currentWallSpecs = new WallSpecs(mouseHit);
      return;
  }

  selecting = true;
  mouseLastX = mouseX;
  mouseLastY = mouseY;
}
function mouseDragged() {
  if (resizing) {
    if (document.documentElement.style.cursor == "e-resize")
      resizingWall.changeW(mouseX - resizingWall.x + 5);
    else if (document.documentElement.style.cursor == "s-resize")
      resizingWall.changeH(mouseY - resizingWall.y + 5);
    else if (document.documentElement.style.cursor == "w-resize")
      resizingWall.changeW(resizingWall.w - (mouseX - resizingWall.x - 5)),
      resizingWall.changeX(mouseX - 5);
    else if (document.documentElement.style.cursor == "n-resize")
      resizingWall.changeH(resizingWall.h - (mouseY - resizingWall.y - 5)),
      resizingWall.changeY(mouseY - 5);
    return;
  }

  if (mouseButton === LEFT) {
    if (dragging || drawing) return;

  let mouseHit = getWall(new Point(mouseX, mouseY));
  if (mouseHit) {
    if (currentWallSpecs) currentWallSpecs.remove();
      mouseHit.isSelected = true;
      draggingOffset = new Point(mouseX - mouseHit.x, mouseY - mouseHit.y);
      dragging = mouseHit;
      canDraw = false;
    }
  }

  if (mouseButton === RIGHT || currentWallSpecs) return;

  if (canDraw)
    drawing = true;
}
function mouseReleased() {
  let mouseHit = getWall(new Point(mouseX, mouseY));
  if (mouseHit) mouseHit.isSelected = !mouseHit.isSelected;

  if (drawing && Math.abs(mouseX - mouseLastX) > 5 && Math.abs(mouseY - mouseLastY) > 5)
    new Wall(mouseLastX, mouseLastY, mouseX - mouseLastX, mouseY - mouseLastY);
  
  if (selecting)
    selecting = false;
  
  dragging = null;
  drawing = false;
  canDraw = true;
  resizing = false;
  resizingWall = null;
  
  return false;
}
function keyPressed() {
  if (keyCode == 27) { // ESC
    if (currentWallSpecs) currentWallSpecs.remove();
    
    canDraw = false;
    drawing = false;
    selecting = false;
  }
  else if (keyCode == 46) { // DELETE
    for (let i = 0; i < walls.length; i++)
      if (walls[i].isSelected)
        walls.splice(i, 1);
  }
}

function exportMap() {
  for (let i = 0; i < walls.length; i++) 
    console.log("new Wall(" + (walls[i].x + walls[i].w/2) + ", " + (walls[i].y + walls[i].h/2) + ", " + walls[i].w + ", " + walls[i].h + ", " + (walls[i].hspd == 0 && walls[i].vspd == 0 ? "false, ": "true, ") + walls[i].vspd + ", " + walls[i].hspd + ");");

  alert("Map kodunuz Konsoldadır!");
}

class Wall {
  constructor(x, y, w, h, hspd = 0, vspd = 0, isAlpha = false, animatedWall = false) {
    this.x = w < 0 ? x + w : x;
    this.y = h < 0 ? y + h : y;
    this.w = w < 0 ? -w : w;
    this.h = h < 0 ? -h : h;
    this.hspd = hspd;
    this.vspd = vspd;
    this.isSelected = false;
    this.isAlpha = isAlpha;

    if (!animatedWall)
      walls.push(this);
    else
      animatedWalls.push(this);
  }

  changeX(x) {
    this.x = this.w < 0 ? x + this.w : x;
  }
  changeY(y) {
    this.y = this.h < 0 ? y + this.h : y;
  }
  changeW(w) {
    if (Math.abs(w) < 8) return;
    this.w = w < 0 ? -w : w;
  }
  changeH(h) {
    if (Math.abs(h) < 8) return;
    this.h = h < 0 ? -h : h;
  }

  move() {
    this.x += this.hspd;
    this.y += this.vspd;

    if (this.x + this.w < 0) this.hspd = -this.hspd;
    else if (this.x > gameWidth) this.hspd = -this.hspd;
    if (this.y + this.h < 0) this.vspd = -this.vspd;
    else if (this.y > gameHeight) this.vspd = -this.vspd;
  }

  draw() {
    push();
    fill(0);
    strokeWeight(5);
    stroke(34,177,11);

    if (this.isSelected) 
      fill('rgba(144, 255, 15, 0.65)');
    if (this.isAlpha)
      stroke('rgba(34, 177, 11, 0.35)'),
      fill('rgba(0, 0, 0, 0.35)');

    rect(this.x, this.y, this.w, this.h);
    pop();
  }
}
class Point {
  constructor (x, y) {
    this.x = x;
    this.y = y;
  }
}
class WallSpecs {
  constructor(wall) {
    this.wall = wall;
    this.inputHSpd = createInput(wall.hspd);
    this.inputVSpd = createInput(wall.vspd);

    this.initInputs();
  }

  updateInputProperties() {
    let _x1 = this.wall.x + this.wall.w/2 - 60;
    let _y1 = this.wall.y - 40;
    let _x2 = this.wall.x + this.wall.w/2 + 10;
    let _y2 = this.wall.y - 40;

    if (_x1 < 0) _x1 = 11;
    else if (_x1 + 140 > windowWidth) _x1 = windowWidth - 140;
    if (_y1 < 0) _y1 = 1;
    if (_x2 < 60) _x2 = 81;
    else if (_x2 + 70 > windowWidth) _x2 = windowWidth - 70;
    if (_y2 < 0) _y2 = 0;

    this.inputHSpd.value(this.wall.hspd);
    this.inputVSpd.value(this.wall.vspd);
    this.inputHSpd.size(50, 25);
    this.inputVSpd.size(50, 25);
    this.inputHSpd.position(_x1, _y1);
    this.inputVSpd.position(_x2, _y2);
  }

  initInputs() {
    var onChangeFunc = (elt, state) => {
      if (Number.isNaN(parseFloat(elt.value()))) {
        if (state == 1) elt.value(this.wall.hspd);
        else if (state == 2) elt.value(this.wall.vspd);
      }

      if (state == 1) this.wall.hspd = parseFloat(elt.value().replace(",", "."));
      else if (state == 2) this.wall.vspd = parseFloat(elt.value().replace(",", "."));

      this.updateInputProperties();
    };

    this.inputHSpd.elt.onchange = () => {onChangeFunc(this.inputHSpd, 1)};
    this.inputVSpd.elt.onchange = () => {onChangeFunc(this.inputVSpd, 2)};

    this.updateInputProperties();
  }

  draw() {
    push();
    fill('rgba(174, 222, 192, 0.6)');
    let _x = this.wall.x + this.wall.w/2 - 68;
    let _y = this.wall.y - 50;
    if (_x < 0) _x = 1;
    if (_x + 140 > windowWidth) _x = windowWidth - 148;
    if (_y < 0) _y = 1;
    
    rect(_x, _y, 140, 50);
    pop();
  }

  remove() {
    this.inputHSpd.remove();
    this.inputVSpd.remove();

    currentWallSpecs = null;
  }
}

function CollisionPointRect(p, bcd) {
  if (p.x > bcd.x && p.x < bcd.x + bcd.w &&
      p.y > bcd.y && p.y < bcd.y + bcd.h) return true;
}

// Prevents Right Click Menu
window.addEventListener("contextmenu", function(e) {
  e.preventDefault();
  return false;
});