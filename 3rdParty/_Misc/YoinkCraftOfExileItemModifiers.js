function RetrieveAll(affixType = "prefixes") {
function GetCoefs(str, numCoefs) {
	let coefs = [0, 0, 0, 0, 0, 0];
	let curIndex = 0;
	const regex = /\((\-)?\d+(\.\d+)?\-(\-)?\d+(\.\d+)?\)|(\d+)|((( )|(^))((\+)|(\-))\d+(\.\d+)?)/gm;
	let allOccurences = str.match(regex);
	if (!allOccurences) { console.log(`ERROR ${allOccurences} ${str}`); return [-1, -2, -1, -2, -1, -2]; }
	for (let i = 0; i < allOccurences.length; ++i) {
		let newRegex = /((?<!\d)\-)?\d+(\.\d+)?/gm;
		let occurences = allOccurences[i].match(newRegex);
		if (occurences.length == 1) {
			coefs[curIndex++] = occurences[0];
			coefs[curIndex++] = occurences[0];
		}
		else if (occurences.length == 2) {
			coefs[curIndex++] = occurences[0];
			coefs[curIndex++] = occurences[1];
		}
		else console.log(`ERROR! INVALID NUMBER OF OCCURENCES! ${occurences.length} ${occurences} ${str}`);
	}
	return coefs;
}
function GetNumCoefs(str) {
	let num = 0;	
	let startIndex = 0;
	let tries = 0;
	while (++tries < 1000 && startIndex != -1) {
		startIndex = str.indexOf("#", startIndex);
		if (startIndex++ == -1) break;
		++num;
	}
	if (tries == 1000) console.log(`ERROR! ---> ${str}`);
	return num;
}
function GetFlag(flag) {
	if (flag == "prefix") return 2;
	else if (flag == "suffix") return 0;
	console.log(`ERROR, GETTING FLAG OF ${flag}`);
	return -1;
}
function GetTagFlag(tags) {
    const _tags = ["Life", "Mana", "Damage", "Defences", "Physical", "Elemental", "Fire", "Cold", "Lightning", "Chaos", "Gem", "Attribute", "Life Regen", "Resistance", "Critical", "Attack", "Curse", "Caster", "Aura", "Ailment", "Minion", "Speed", "Bleed", "Influence", "Poison"];

    let result = 0;
    
    for(let i = 0; i < tags.length; ++i) {
        let currentTag = tags[i];
        let index = 0;
        for (; index < _tags.length; ++index)
            if (_tags[index] == currentTag) break;

        if (index == _tags.length) {
            if (currentTag != "Armor" && currentTag != "Evasion" && currentTag != "Energy Shield")
	    	console.log(`ERROR! Tag '${currentTag}' was not found.`);
            continue;
        }

        result += Math.pow(2, index);
    }

    return result;
}
function FindTags(str) {
	//console.log(str);
	let tags = [];
	let lastIndex = str.indexOf("Tag\">");
	if (lastIndex != -1) lastIndex += 5;
	//console.log(lastIndex);
	let maxTries = 0;
	while(++maxTries < 1000 && lastIndex != -1) {
		let endIndex = str.indexOf("<", lastIndex);
		tags.push(str.substring(lastIndex, endIndex));
		lastIndex = str.indexOf(`Tag">`, lastIndex);
		if (lastIndex == -1) break;
		lastIndex += 5;
	}
	if (maxTries == 1000) console.log("error!");
	return tags;
}
function GetFormat(str) {
	let format = "";
	let startIndex = str.indexOf("<div>") + 5;
	let endIndex = str.indexOf("<div", startIndex);
	if (startIndex != -1 && endIndex != -1) format = str.substring(startIndex, endIndex);
	return format;
}

let prefixesHTML = document.getElementsByClassName(affixType)[0].children[2].children;
let allPrefixes = [];
for (let i = 1; i < prefixesHTML.length - 1; ++i)
    allPrefixes.push(prefixesHTML[i]);
let prefixes = [];
let j = -1;
for (let i = 0; i < allPrefixes.length; ++i) {
    let prefixHTML = allPrefixes[i];
    if (prefixHTML.className.indexOf("main") != -1) {
        let prefixGroup = prefixHTML.getAttribute("amodgrp");
        let _tags = FindTags(prefixHTML.innerHTML);
        let _format = GetFormat(prefixHTML.innerHTML);
	let _numCoefs = GetNumCoefs(_format);
        //prefixGroup = prefixGroup.substring(prefixGroup.indexOf("_") + 1);
        prefixes.push({BaseItemModifierType:{Name:prefixGroup, TagFlags: GetTagFlag(_tags), Tags:_tags}, BaseItemModifierTypes:[], Format:_format, NumCoefs: _numCoefs, HTML_main:prefixHTML, HTML_subTiers:[]});
        ++j;
        continue;
    }

    prefixes[j].HTML_subTiers.push(prefixHTML);
    let tier = prefixHTML.getAttribute("tier");
    let ilvl = prefixHTML.getAttribute("ilvl");
    let type = GetFlag(prefixHTML.getAttribute("atype"));
    let weight = prefixHTML.children[3].innerText;
    let coefs = GetCoefs(prefixHTML.children[0].innerText, prefixes[j].NumCoefs);
    let _format = prefixes[j].Format;
    prefixes[j].BaseItemModifierTypes.push({Name:prefixHTML.getAttribute("modgrp")+"T"+tier, Tier: tier, ItemLevel: ilvl, Flags: type, Weight: weight, Format: _format, Coefs: coefs});
}
for (let i = 0; i < prefixes.length; ++i) {
    if (prefixes[i].HTML_subTiers.length == 1) {
        console.log("ERROR, NEED MANUAL INTERVENTION");
        console.log(prefixes[i]);
        prefixes[i].HTML_subTiers = [];
        prefixes[i].HTML_subTiers.push(prefixes[i].HTML_main);
    }
}

	return prefixes;
}
function FormatToDBBaseItemModifiers(arr, filterArr) {
	let str = "";
	for (let a = 0; a < arr.length; ++a) {
		for (let i = 0; i < arr[a].BaseItemModifierTypes.length; ++i) {
			let d = arr[a].BaseItemModifierTypes[i];
			let exists = false;
			for (let j = 0; j < filterArr.length; ++j)
				if (filterArr[j].name == d.Name && filterArr[j].format == d.Format) { exists = true; break; }
			if (exists) continue;			
			str += d.Name + "\t";
			str += d.Tier + "\t";
			str += "-1\t";
			str += d.Flags + "\t";
			for (let j = 0; j < d.Coefs.length; ++j)
				str += d.Coefs[j] + "\t";
			str += d.Weight + "\t";
			str += d.ItemLevel + "\t";
			str += (d.Format.indexOf("#") == -1 ? "-1": d.Format) + "\n";
		}
	}
	return str;
}
function FormatToDBBaseItemModifierTypes(arr) {
	let str = "";
	for (let i = 0; i < arr.length; ++i) {
		let d = arr[i].BaseItemModifierType;
		str += d.Name + "\t";
		str += d.TagFlags + "\n";
	}
	return str;
}


// configs
let cells = ``;
if (cells.length < 10) { console.log("error, no cells found"); }
else {
let splitCells = cells.split("\n");
let allObjs = [];
for (let i = 0; i < splitCells.length; ++i) {
    let k = splitCells[i].split("\t");
    allObjs.push({name:k[0],format:k[k.length-1]});
}

let affixes = RetrieveAll("prefixes");
affixes.push(...RetrieveAll("suffixes"));
let dbModifiers = FormatToDBBaseItemModifiers(affixes, allObjs);

console.log(dbModifiers); }