#include "Zombie.h"
#include "../../Miscellaneous/Random.h"
#include "../../Miscellaneous/Log.h"

// [To-Do] 
// After you implement a Shader class, dump these and switch to using a simple shader color outlining the sprite.
static std::string commonRarity_TexturePath = "assets/sprites/monsters/zombie/common.png";
static std::string magicRarity_TexturePath = "assets/sprites/monsters/zombie/magic.png";
static std::string rareRarity_TexturePath = "assets/sprites/monsters/zombie/rare.png";
static std::string uniqueRarity_TexturePath = "assets/sprites/monsters/zombie/unique.png";
static std::string all_TexturePaths[4] = { commonRarity_TexturePath, magicRarity_TexturePath, rareRarity_TexturePath, uniqueRarity_TexturePath };

Zombie::Zombie() : Zombie("Zombie") {};
Zombie::Zombie(std::string _name): Monster(_name) {
	renderer.AssignTexture(all_TexturePaths[(int)rarity]);
};