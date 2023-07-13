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
    constructor(ID = 0, type = 0, posX = 0, posY = 0) {
        this.ID = ID;
        this.type = type;
        this.posX = posX;
        this.posY = posY;
    }

    export() {
        return { "ID": this.ID, "Type": this.type, "PosX": this.posX, "PosY": this.posY };
    }
}