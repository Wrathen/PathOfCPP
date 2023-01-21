#pragma once
#include <string>
#include "../../../Miscellaneous/Random.h"

// I think it's better to store all the strings rather than 
// Creating the strings dynamically on demand.
// Let's assume at most each path will take 50 characters and it's unicode so 100 bytes
// Let's assume at most there will be 13 different item types (which probably wont)
// And each item type will have on average 30 sprites.
// 100 * 30 * 13 = 39000 bytes -> ~38kbs of memory
// GetRandomHelm = () => { return "assets/sprites/Item/Equipment/Helm/" + random(0, 15); }

const static std::string texturePaths_Chest[] = {
	"assets/sprites/Item/Equipment/Chest/0.png",
	"assets/sprites/Item/Equipment/Chest/1.png",
	"assets/sprites/Item/Equipment/Chest/2.png",
	"assets/sprites/Item/Equipment/Chest/3.png",
	"assets/sprites/Item/Equipment/Chest/4.png",
	"assets/sprites/Item/Equipment/Chest/5.png",
	"assets/sprites/Item/Equipment/Chest/6.png",
	"assets/sprites/Item/Equipment/Chest/7.png",
	"assets/sprites/Item/Equipment/Chest/8.png",
	"assets/sprites/Item/Equipment/Chest/9.png",
	"assets/sprites/Item/Equipment/Chest/10.png",
	"assets/sprites/Item/Equipment/Chest/11.png",
	"assets/sprites/Item/Equipment/Chest/12.png",
	"assets/sprites/Item/Equipment/Chest/13.png",
	"assets/sprites/Item/Equipment/Chest/14.png",
	"assets/sprites/Item/Equipment/Chest/15.png",
	"assets/sprites/Item/Equipment/Chest/16.png",
	"assets/sprites/Item/Equipment/Chest/17.png",
	"assets/sprites/Item/Equipment/Chest/18.png",
	"assets/sprites/Item/Equipment/Chest/19.png",
	"assets/sprites/Item/Equipment/Chest/20.png",
	"assets/sprites/Item/Equipment/Chest/21.png",
	"assets/sprites/Item/Equipment/Chest/22.png",
	"assets/sprites/Item/Equipment/Chest/23.png",
	"assets/sprites/Item/Equipment/Chest/24.png",
	"assets/sprites/Item/Equipment/Chest/25.png",
	"assets/sprites/Item/Equipment/Chest/26.png",
	"assets/sprites/Item/Equipment/Chest/27.png",
	"assets/sprites/Item/Equipment/Chest/28.png",
	"assets/sprites/Item/Equipment/Chest/29.png",
	"assets/sprites/Item/Equipment/Chest/30.png",
	"assets/sprites/Item/Equipment/Chest/31.png",
	"assets/sprites/Item/Equipment/Chest/32.png",
	"assets/sprites/Item/Equipment/Chest/33.png",
	"assets/sprites/Item/Equipment/Chest/34.png",
	"assets/sprites/Item/Equipment/Chest/35.png",
	"assets/sprites/Item/Equipment/Chest/36.png",
	"assets/sprites/Item/Equipment/Chest/37.png",
	"assets/sprites/Item/Equipment/Chest/38.png",
	"assets/sprites/Item/Equipment/Chest/39.png",
	"assets/sprites/Item/Equipment/Chest/40.png",
	"assets/sprites/Item/Equipment/Chest/41.png",
	"assets/sprites/Item/Equipment/Chest/42.png",
	"assets/sprites/Item/Equipment/Chest/43.png",
	"assets/sprites/Item/Equipment/Chest/44.png",
	"assets/sprites/Item/Equipment/Chest/45.png",
	"assets/sprites/Item/Equipment/Chest/46.png",
	"assets/sprites/Item/Equipment/Chest/47.png",
	"assets/sprites/Item/Equipment/Chest/48.png",
	"assets/sprites/Item/Equipment/Chest/49.png",
	"assets/sprites/Item/Equipment/Chest/50.png",
	"assets/sprites/Item/Equipment/Chest/51.png",
	"assets/sprites/Item/Equipment/Chest/52.png",
	"assets/sprites/Item/Equipment/Chest/53.png",
	"assets/sprites/Item/Equipment/Chest/54.png",
	"assets/sprites/Item/Equipment/Chest/55.png",
	"assets/sprites/Item/Equipment/Chest/56.png",
	"assets/sprites/Item/Equipment/Chest/57.png",
	"assets/sprites/Item/Equipment/Chest/58.png",
	"assets/sprites/Item/Equipment/Chest/59.png",
	"assets/sprites/Item/Equipment/Chest/60.png",
	"assets/sprites/Item/Equipment/Chest/61.png",
	"assets/sprites/Item/Equipment/Chest/62.png",
	"assets/sprites/Item/Equipment/Chest/63.png"
};
const static std::string texturePaths_Helm[] = {
	"assets/sprites/Item/Equipment/Helm/0.png",
	"assets/sprites/Item/Equipment/Helm/1.png",
	"assets/sprites/Item/Equipment/Helm/2.png",
	"assets/sprites/Item/Equipment/Helm/3.png",
	"assets/sprites/Item/Equipment/Helm/4.png",
	"assets/sprites/Item/Equipment/Helm/5.png",
	"assets/sprites/Item/Equipment/Helm/6.png",
	"assets/sprites/Item/Equipment/Helm/7.png",
	"assets/sprites/Item/Equipment/Helm/8.png",
	"assets/sprites/Item/Equipment/Helm/9.png",
	"assets/sprites/Item/Equipment/Helm/10.png",
	"assets/sprites/Item/Equipment/Helm/11.png",
	"assets/sprites/Item/Equipment/Helm/12.png",
	"assets/sprites/Item/Equipment/Helm/13.png",
	"assets/sprites/Item/Equipment/Helm/14.png",
	"assets/sprites/Item/Equipment/Helm/15.png",
};
const static std::string texturePaths_Cloak[] = {
	"assets/sprites/Item/Equipment/Cloak/0.png",
	"assets/sprites/Item/Equipment/Cloak/1.png",
	"assets/sprites/Item/Equipment/Cloak/2.png",
	"assets/sprites/Item/Equipment/Cloak/3.png",
	"assets/sprites/Item/Equipment/Cloak/4.png",
	"assets/sprites/Item/Equipment/Cloak/5.png",
	"assets/sprites/Item/Equipment/Cloak/6.png",
	"assets/sprites/Item/Equipment/Cloak/7.png"
};
const static std::string texturePaths_Amulet[] = {
	"assets/sprites/Item/Equipment/Amulet/0.png",
	"assets/sprites/Item/Equipment/Amulet/1.png",
	"assets/sprites/Item/Equipment/Amulet/2.png",
	"assets/sprites/Item/Equipment/Amulet/3.png",
	"assets/sprites/Item/Equipment/Amulet/4.png",
	"assets/sprites/Item/Equipment/Amulet/5.png",
	"assets/sprites/Item/Equipment/Amulet/6.png",
	"assets/sprites/Item/Equipment/Amulet/7.png"
};
const static std::string texturePaths_Feet[] = {
	"assets/sprites/Item/Equipment/Feet/0.png",
	"assets/sprites/Item/Equipment/Feet/1.png",
	"assets/sprites/Item/Equipment/Feet/2.png",
	"assets/sprites/Item/Equipment/Feet/3.png",
	"assets/sprites/Item/Equipment/Feet/4.png",
	"assets/sprites/Item/Equipment/Feet/5.png",
	"assets/sprites/Item/Equipment/Feet/6.png",
	"assets/sprites/Item/Equipment/Feet/7.png"
};
const static std::string texturePaths_Ring[] = {
	"assets/sprites/Item/Equipment/Ring/0.png",
	"assets/sprites/Item/Equipment/Ring/1.png",
	"assets/sprites/Item/Equipment/Ring/2.png",
	"assets/sprites/Item/Equipment/Ring/3.png",
	"assets/sprites/Item/Equipment/Ring/4.png",
	"assets/sprites/Item/Equipment/Ring/5.png",
	"assets/sprites/Item/Equipment/Ring/6.png",
	"assets/sprites/Item/Equipment/Ring/7.png"
};

const inline std::string& GetRandomTexturePath_Chest() {
	return texturePaths_Chest[RandomInt(64)];
}
const inline std::string& GetRandomTexturePath_Helm() {
	return texturePaths_Helm[RandomInt(16)];
}
const inline std::string& GetRandomTexturePath_Cloak() {
	return texturePaths_Cloak[RandomInt(8)];
}
const inline std::string& GetRandomTexturePath_Amulet() {
	return texturePaths_Amulet[RandomInt(8)];
}
const inline std::string& GetRandomTexturePath_Feet() {
	return texturePaths_Feet[RandomInt(8)];
}
const inline std::string& GetRandomTexturePath_Ring() {
	return texturePaths_Ring[RandomInt(8)];
}