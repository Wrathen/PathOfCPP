// Utility Functions
function getMouseScreenX() { return mouseX; }
function getMouseScreenY() { return mouseY; }
function getMouseWorldX() { return (mouseX + cameraOffsetScaled[0]) / zoom; }
function getMouseWorldY() { return (mouseY + cameraOffsetScaled[1]) / zoom; }
function getZoneName() { return UIElements[4].value(); }
function getGrid(x, y) { return [(x / gridSizeX) | 0, (y / gridSizeY) | 0]; }

// Utility UI Functions
function getUIShowHideButton() { return UIElements[0]; }
function isUIPanelHidden() { return getUIShowHideButton().elt.innerHTML == "Show"; }