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
    "Select": 1,
    "TileInsert": 2,
    "ZoneInsert": 3,
    "EntityInsert": 4,
}
const SelectionType = {
    "None": 0,
    "Entity": 1,
    "Collider": 2,
    "SpawnZone": 3,
    "Portal": 4
}
const ZoneInsertType = {
    "Collider": 0,
    "SpawnZone": 1,
    "Portal": 2
}
const ObjectType = {
    "Tile": 0,
    "Entity": 1,
    "Collider": 2,
    "SpawnZone": 3,
    "Portal": 4
}