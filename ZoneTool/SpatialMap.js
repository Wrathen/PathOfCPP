class SpatialMap {
    constructor(mapWidth, mapHeight, cellWidth, cellHeight) {
        this.mapWidth = mapWidth;
        this.mapHeight = mapHeight;
        this.cellWidth = cellWidth;
        this.cellHeight = cellHeight;
        this.cellAmountX = (this.mapWidth / this.cellWidth) | 0;
        this.cellAmountY = (this.mapHeight / this.cellHeight) | 0;

        this.isInitialized = false;
    }

    init() {
        this.cells = new Array(this.cellAmountX * this.cellAmountY);
        this.isInitialized = true;
    }
    add(object, x, y) {
        let cellIndex = this.getCellIndex(x, y);
        this.cells[cellIndex.x + cellIndex.y * this.cellAmountX] = object;
    }
    removeObject(object) {
        // Check whether the object was in their location.
        if (this.get(object.x, object.y) != object)
            console.log("[WARNING] When trying to remove an object from spatial map, they couldn't be found on their previous location!");
        else this.remove(object.x, object.y);
    }
    remove(x, y) {
        let cellIndex = this.getCellIndex(x, y);
        this.cells[cellIndex.x + cellIndex.y * this.cellAmountX] = null;
    }
    getCellIndex(x, y) {
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        return { "x": (x / this.cellWidth) | 0, "y": (y / this.cellHeight) | 0 };
    }
    get(x, y) {
        if (!this.cells) {
            console.log("[ERROR] Spatial Map is not initialized!");
            return null;
        }

        let cellIndex = this.getCellIndex(x, y);
        return this.cells[cellIndex.x + cellIndex.y * this.cellAmountX];
    }
    move(object, x, y) {
        this.removeObject(object);
        this.add(object, x, y);
    }
}