// How-to-use?
// Paste it into the console and copy the unique asset links for base item types.
// For example:
// - Go to https://poedb.tw/us/Two_Hand_Swords
// - Click on Two-Hand Swords Item sub-section
// - Paste the code into console
// - Yoink all the URL's for unique item asset links (.png's)
// - Download them manually afterwards :^)

let a = document.getElementsByClassName("table-responsive");
let c = a[a.length-1];
let d = c.children[0].children[1];
let f = [];
for (let i = 0; i < d.children.length; ++i) {
    let e = d.children[i];
	let s = e.children[0].children[0].children[0].src;
	if (!f.includes(s)) f.push(s);
}
function logFormatted(arr) {
	let s = ``;
	for (let i = 0; i < arr.length; ++i)
		s += arr[i] + "\n";
	return s;
}
console.log(logFormatted(f));