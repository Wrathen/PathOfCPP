// global object count
let gObjectCount = 0;

class ZoneGeneralData {
    constructor(ZoneName = "Unnamed Zone") {
        this.name = ZoneName;
        this.monsterLevel = 1;
    }

    export() {
        return { "Name": this.name, "MonsterLevel": this.monsterLevel };
    }
}
class ZoneBackgroundData {
    constructor(bgPath = "assets/sprites/nosprite.png") {
        this.bgPath = bgPath;
    }

    export() {
        return { "Path": this.bgPath };
    }
}

class Tile {
    constructor(img, x, y, w = 16, h = 16) {
        this.GUID = ++gObjectCount;
        this.img = img;
        this.x = x;
        this.y = y;
        this.w = gridsEnabled ? gridSizeX : w;
        this.h = gridsEnabled ? gridSizeY : h;

        this.objectType = ObjectType.Tile;
    }

    // utils
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