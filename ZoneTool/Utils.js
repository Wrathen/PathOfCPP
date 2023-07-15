// Util Classes
class Point {
    constructor(x, y) { this.x = x; this.y = y; }

    intersectsRect(rect) {
        return this.x > rect.x && this.x < rect.x + rect.w &&
            this.y > rect.y && this.y < rect.y + rect.h;
    }
}
class Rect {
    constructor(x, y, w, h) { this.x = x; this.y = y; this.w = w; this.h = h; }
}

// Utility Functions
function getMouseScreenX() { return mouseX; }
function getMouseScreenY() { return mouseY; }
function getMouseWorldX() { return (mouseX + cameraOffsetScaled[0]) / zoom; }
function getMouseWorldY() { return (mouseY + cameraOffsetScaled[1]) / zoom; }
function screenToWorld(pos, offset = cameraOffsetScaled) { return new Point((pos.x + offset[0]) / zoom, (pos.y + offset[1]) / zoom); }
function worldToScreen(pos, offset = cameraOffsetScaled) { return new Point((pos.x - offset[0]) * zoom, (pos.y - offset[1]) * zoom); }
function getZoneName() { return UIElements[4].value(); }
function getGrid(x, y) { return [x < 0 ? 0 : (x / gridSizeX) | 0, y < 0 ? 0 : (y / gridSizeY) | 0]; }
// @todo euler distance algorithm
function getDistance(x1, y1, x2, y2) { return Math.abs(x1 - x2) + Math.abs(y1 - y2); }
// Manhattan Distance algorithm
function getDistanceFast(x1, y1, x2, y2) { return Math.abs(x1 - x2) + Math.abs(y1 - y2); }
function getEntityByID(id) { for (let i = 0; i < EntityTypes.length; ++i) if (EntityTypes[i].ID == id) return EntityTypes[i]; return null; }
function hasValidSelection() { return currentSelection; }

// Utility UI Functions
function getUIShowHideButton() { return UIElements[0]; }
function isUIPanelHidden() { return getUIShowHideButton().elt.innerHTML == "Show"; }
function getUIZoneName() { return UIElements[4]; }
function getUIBackgroundPath() { return UIElements[6]; }

// Global Utilities
function shuffleArray(array) {
    for (var i = array.length - 1; i > 0; --i) {
        var j = Math.floor(Math.random() * (i + 1));
        var temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}