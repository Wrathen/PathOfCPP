// This code is totally garbage but works and is meant for
// to yoink database information from poedb.tw
// Specifically used in base weapon items such as
// https://poedb.tw/us/Daggers#DaggersItem or https://poedb.tw/us/Wands#WandsItem

// How to use?:
// go to https://poedb.tw/us/Claws click on (Claws Item /28) and copy paste this whole code into console, copy the output, and use the SQL query.
// this is working as of today 9th of August 2023. Yoinked over 400 base weapons :^)


// base item type ID, you need to change this if you, say wanna retrieve Wand, it should be 3, instead of 1 ("Claw");
let __id = 1;
let __imgPathPrefixes = ["", "Claw", "Dagger", "Wand", "Sword1H", "Rapier", "Axe1H", "Mace1H", "Sceptre", "RuneDagger", "Bow", "Staff", "Sword2H",
                            "Axe2H", "Mace2H", "Warstaff", "FishingRod", "Quiver", "Shield"]; 

let data = document.getElementsByClassName("tab-pane fade active show")[0].children[1].children[2].children[0].tBodies[0].innerHTML;

let tdIndex = data.indexOf("<td>", 0);
let isImg = true;

let retrieveSubstring = (seekBegin, seekEnd) => {
    let endIndex = data.indexOf(seekEnd, tdIndex);
    let currentIndex = endIndex - seekBegin.length + 1;
    while (--currentIndex >= 0 && data.substring(currentIndex, currentIndex + seekBegin.length) != seekBegin);
    if (currentIndex == -1) { console.log("Error! " + tdIndex + ", " + seekBegin + ", " + seekEnd + ", " + currentIndex + ", " + endIndex); return ""; }
    tdIndex = endIndex + seekEnd.length;
    return data.substring(currentIndex + seekBegin.length, endIndex);
};
let retrieveSubstringCustom = (str, startIndex, seekBegin, seekEnd) => {
    let endIndex = str.indexOf(seekEnd, startIndex);
    let currentIndex = endIndex - seekBegin.length + 1;
    while (--currentIndex >= 0 && str.substring(currentIndex, currentIndex + seekBegin.length) != seekBegin);
    if (currentIndex == -1) { console.log("Error custom retrieve substring! " + startIndex + ", " + seekBegin + ", " + seekEnd + ", " + currentIndex + ", " + endIndex); return { "substr": "", "index": -1 }; }

    return { "substr": str.substring(currentIndex + seekBegin.length, endIndex), "index": endIndex + seekEnd.length };
};
let _items = [];
let currentItem = {};
while (tdIndex != -1) {
    if (isImg) {
        let imgPath = retrieveSubstring("/", ".png");
        if (imgPath == "") break;
        currentItem["ImgPath"] = imgPath + ".png";
    }
    else {
        // Item Name
        {
            let itemName = retrieveSubstring(">", "</a>");
            if (itemName == "") break;
            currentItem["ItemName"] = itemName;
        }
        // Physical Damage
        {
            let phys = retrieveSubstring(">", "</span>");
            if (phys == "") break;
            currentItem["PhysicalDamage"] = phys;
        }
        // Crit Chance
        {
            let val = retrieveSubstring(">", "</span>");
            if (val == "") break;
            currentItem["CritChance"] = val;
        }
        // Attacks Per Second
        {
            let val = retrieveSubstring(">", "</span>");
            if (val == "") break;
            currentItem["AttacksPerSecond"] = val;
        }
        // Weapon Range
        {
            let weaponRangeExists = data.indexOf("Weapon Range", tdIndex) != -1;
            if (weaponRangeExists) {
                let val = retrieveSubstring(">", "</span>");
                if (val == "") break;
                currentItem["WeaponRange"] = val;
            }
        }
        // Requirements
        {
            let reqIndex = data.indexOf("<div class=\"requirements\">", tdIndex);
            let reqEndIndex = data.indexOf("</div>", reqIndex);
            let requirementData = data.substring(reqIndex, reqEndIndex + 6);
            if (reqIndex == -1)
                console.log("error: no requirements div found, continuing with no requirements");
            else {
                tdIndex = reqIndex;
                currentItem["Requirements"] = {};
                // Level
                {
                    let val = retrieveSubstring("Requires", "<span");
                    if (val == "") break;
                    let valIndex = val.indexOf("Level");
                    if (valIndex != -1) {
                        let _val = retrieveSubstring(">", "</span>");
                        if (_val == "") break;
                        currentItem["Requirements"]["Level"] = _val;
                    }
                }
                // Str-Dex-Int
                //console.log(requirementData);
                let lastRequirementIndex = 0;
                for (let i = 0; i < 3; ++i) {
                    lastRequirementIndex = requirementData.indexOf("<span class=\"text-type0\">", lastRequirementIndex) + 25;
                    let _val = retrieveSubstringCustom(requirementData, lastRequirementIndex, "<span class=\"text-type0\">", "</span>");
                    //console.log(_val);
                    if (_val["substr"] == "" || _val["index"] == -1) continue;
                    let att = requirementData.substring(_val["index"] + 1, _val["index"] + 4);
                    //console.log(att);
                    if (!(att != "Str" && att != "Dex" && att != "Int") && !currentItem["Requirements"][att])
                        currentItem["Requirements"][att] = _val["substr"];
                }
            }
        }
    }

    tdIndex = data.indexOf("<td>", tdIndex + 4);
    isImg = !isImg;
    if (isImg) {
        _items.push(currentItem);
        currentItem = {};
    }
}

// Ex: convertItemsToSQLInsert("BaseItemsWeapons", 1); 1 means Claw
function convertItemsToSQLInsert(tableName, itemTypeID, imgPathPrefix) {
    let sqlData = "";
    let columns = "Name, ItemTypeID, ImagePath, RequiredLevel, RequiredSTR, RequiredDEX, RequiredINT, BasePhysicalDamageMin, BasePhysicalDamageMax, BaseCritChance, BaseAttacksPerSecond, BaseWeaponRange";

    for (let i = 0; i < _items.length; ++i) {
        let it = _items[i];
        sqlData += `("${it.ItemName}", `
                 + `${itemTypeID}, `
                 + `"${imgPathPrefix + it.ImgPath}", `
                 + `${it.Requirements && it.Requirements["Level"] ? it.Requirements["Level"] : 0}, `
                 + `${it.Requirements && it.Requirements["Str"] ? it.Requirements["Str"] : 0}, `
                 + `${it.Requirements && it.Requirements["Dex"] ? it.Requirements["Dex"] : 0}, `
                 + `${it.Requirements && it.Requirements["Int"] ? it.Requirements["Int"] : 0}, `
                 + `${it.PhysicalDamage.substring(0, it.PhysicalDamage.indexOf("-"))}, `
                 + `${it.PhysicalDamage.substring(it.PhysicalDamage.indexOf("-") + 1)}, `
                 + `${it.CritChance.substr(0, it.CritChance.length - 1)}, `
                 + `${it.AttacksPerSecond}, `
                 + `${it.WeaponRange ? it.WeaponRange : 0}), `;
    }

    // remove the ',' at the end.
    sqlData = sqlData.substring(0, sqlData.length - 2);

    return `INSERT INTO ${tableName} (${columns}) VALUES${sqlData}`;
}

// Ease-of-use.
{
    //console.log(_items);
    convertItemsToSQLInsert("BaseItemsWeapons", __id, `Assets\\Sprites\\Item\\${__imgPathPrefixes[__id]}\\`);
}