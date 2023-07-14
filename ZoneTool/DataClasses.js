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
class ZoneColliderData {
    constructor(posX = 0, posY = 0, w = 0, h = 0) {
        this.posX = posX;
        this.posY = posY;
        this.w = w;
        this.h = h;
    }

    export() {
        return { "PosX": this.posX, "PosY": this.posY, "Width": this.w, "Height": this.h };
    }
}
class ZoneSpawnZoneData {
    constructor(posX = 0, posY = 0, w = 0, h = 0, amount = 0) {
        this.posX = posX;
        this.posY = posY;
        this.w = w;
        this.h = h;
        this.amount = amount;
    }

    export() {
        return { "PosX": this.posX, "PosY": this.posY, "Width": this.w, "Height": this.h, "Amount": this.amount };
    }
}
class ZonePortalData {
    constructor(posX = 0, posY = 0, w = 0, h = 0) {
        this.posX = posX;
        this.posY = posY;
        this.w = w;
        this.h = h;
        this.nextZone = "Empty";
    }

    export() {
        return { "PosX": this.posX, "PosY": this.posY, "Width": this.w, "Height": this.h, "NextZone": this.nextZone };
    }
}
class ZoneEntityData {
    constructor(id = 0, type = 0, posX = 0, posY = 0) {
        this.id = id;
        this.type = type;
        this.posX = posX;
        this.posY = posY;
    }

    export() {
        return { "ID": this.id, "Type": this.type, "PosX": this.posX, "PosY": this.posY };
    }
}

class Tile {
    constructor(img, x, y, w = 16, h = 16) {
        this.GUID = ++gObjectCount;
        this.img = img;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;

        this.objectType = ObjectType.Tile;
    }

    // main
    deleteData() { deleteTileData(this); }

    // utils
    getWorldX() { return this.x * zoom - this.getRenderWidth() / 2 - cameraOffsetScaled[0]; }
    getWorldY() { return this.y * zoom - this.getRenderHeight() / 2 - cameraOffsetScaled[1]; }
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
    // main
    deleteData() { deleteEntityData(this); }

    // utils
    getWorldX() { return this.x * zoom - this.getRenderWidth() / 2 - cameraOffsetScaled[0]; }
    getWorldY() { return this.y * zoom - this.getRenderHeight() / 2 - cameraOffsetScaled[1]; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }
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

    deleteData() { deleteColliderData(this); }
    getWorldX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getWorldY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }
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

    deleteData() { deleteSpawnZoneData(this); }
    getWorldX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getWorldY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }
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

    deleteData() { deletePortalData(this); }
    getWorldX() { return this.x * zoom - cameraOffsetScaled[0]; }
    getWorldY() { return this.y * zoom - cameraOffsetScaled[1]; }
    getRenderWidth() { return this.w * zoom; }
    getRenderHeight() { return this.h * zoom; }
}