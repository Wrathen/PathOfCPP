// global object count
let gObjectCount = 0;

class ZoneGeneralData {
    constructor(ZoneName = "Unnamed Zone") {
        this.name = ZoneName;
        this.monsterLevel = 1;
    }

    import(data) {
        this.name = data.Name;
        this.monsterLevel = data.MonsterLevel;
    }
    export() {
        return { "Name": this.name, "MonsterLevel": this.monsterLevel };
    }
}
class ZoneBackgroundData {
    constructor(bgPath = "assets/sprites/nosprite.png") {
        this.bgPath = bgPath;
    }

    import(data) {
        this.bgPath = data.Path;
    }
    export() {
        return { "Path": this.bgPath };
    }
}

class Tile {
    constructor(img, x, y, w = gridSizeX, h = gridSizeY) {
        this.GUID = ++gObjectCount;
        this.img = img;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;

        this.objectType = ObjectType.Tile;
    }

    // utils
    move(pos) {
        // update spatial map with our desired location.
        spatialMap.move(this, pos.x, pos.y);

        this.x = pos.x;
        this.y = pos.y;
    }
    delete() { spatialMap.removeObject(this); delete this; }

    getScreenX() { return this.x * zoom - this.getRenderWidth() / 2 - cameraOffsetScaled[0]; }
    getScreenY() { return this.y * zoom - this.getRenderHeight() / 2 - cameraOffsetScaled[1]; }
    getWorldX() { return (this.x + cameraOffsetScaled[0]) / zoom; }
    getWorldY() { return (this.y + cameraOffsetScaled[1]) / zoom; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }
}
class Entity {
    constructor(id, type, img, x, y) {
        this.GUID = ++gObjectCount;
        this.id = id;
        this.type = type;
        this.img = img;
        this.x = x;
        this.y = y;
        this.w = 64;
        this.h = 64;

        this.objectType = ObjectType.Entity;
    }

    // utils
    move(pos) { this.x = pos.x; this.y = pos.y; }
    delete() { delete this; }
    getScreenX() { return this.x * zoom - this.getRenderWidth() / 2 - cameraOffsetScaled[0]; }
    getScreenY() { return this.y * zoom - this.getRenderHeight() / 2 - cameraOffsetScaled[1]; }
    getWorldX() { return (this.x + cameraOffsetScaled[0]) / zoom; }
    getWorldY() { return (this.y + cameraOffsetScaled[1]) / zoom; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }

    export() {
        return { "ID": this.id, "Type": this.type, "PosX": this.x, "PosY": this.y };
    }
}
class Collider {
    constructor(x, y, w, h) {
        this.GUID = ++gObjectCount;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;

        this.objectType = ObjectType.Collider;
    }

    // utils
    move(pos) { this.x = pos.x; this.y = pos.y; }
    delete() { delete this; }
    getScreenX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getScreenY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getWorldX() { return (this.x + cameraOffsetScaled[0]) / zoom; }
    getWorldY() { return (this.y + cameraOffsetScaled[1]) / zoom; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }

    export() {
        return { "PosX": this.x, "PosY": this.y, "Width": this.w, "Height": this.h };
    }
}
class SpawnZone {
    constructor(x, y, w, h) {
        this.GUID = ++gObjectCount;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.amount = 0;

        this.objectType = ObjectType.SpawnZone;
    }

    // utils
    move(pos) { this.x = pos.x; this.y = pos.y; }
    delete() { delete this; }
    getScreenX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getScreenY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getWorldX() { return (this.x + cameraOffsetScaled[0]) / zoom; }
    getWorldY() { return (this.y + cameraOffsetScaled[1]) / zoom; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }

    export() {
        return { "PosX": this.x, "PosY": this.y, "Width": this.w, "Height": this.h, "Amount": this.amount };
    }
}
class Portal {
    constructor(x, y, w, h) {
        this.GUID = ++gObjectCount;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.nextZone = "";

        this.objectType = ObjectType.Portal;
    }

    // utils
    move(pos) { this.x = pos.x; this.y = pos.y; }
    delete() { delete this; }
    getScreenX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getScreenY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getWorldX() { return (this.x + cameraOffsetScaled[0]) / zoom; }
    getWorldY() { return (this.y + cameraOffsetScaled[1]) / zoom; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }

    export() {
        return { "PosX": this.x, "PosY": this.y, "Width": this.w, "Height": this.h, "NextZone": this.nextZone };
    }
}