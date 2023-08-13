// Usage:
// Call the function and pass in an array of modifier tags.
// For example, #% of Physical Damage from Hits taken as Lightning Damage modifier has the tags Elemental Lightning Physical
// Just do GetTagFlag(["Elemental", "Lightning", "Physical"]) to retrieve the integer flag number and input that into the Database.

function GetTagFlag(tags) {
    const _tags = ["Life", "Mana", "Damage", "Defences", "Physical", "Elemental", "Fire", "Cold", "Lightning", "Chaos", "Gem", "Attribute", "LifeRegen", "Resistance", "Critical", "Attack", "Curse", "Caster", "Aura", "Ailment", "Minion", "Speed", "Bleed", "Influence", "Poison"];

    let result = 0;
    
    for(let i = 0; i < tags.length; ++i) {
        let currentTag = tags[i];
        let index = 0;
        for (; index < _tags.length; ++index)
            if (_tags[index] == currentTag) break;

        if (index == _tags.length) {
            console.log(`ERROR! Tag '${currentTag}' was not found.`);
            return -1;
        }

        result += Math.pow(2, index);
    }

    return result;
}