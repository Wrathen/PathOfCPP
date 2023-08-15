#include "Zombie.h"
#include "../../Miscellaneous/Random.h"
#include "../../Miscellaneous/Log.h"

// [To-Do] 
// After you implement a Shader class, dump these and switch to using a simple shader color outlining the sprite.
static const std::string commonRarity_TexturePath = "Assets/Sprites/Monsters/Zombie/common.png";
static const std::string magicRarity_TexturePath = "Assets/Sprites/Monsters/Zombie/magic.png";
static const std::string rareRarity_TexturePath = "Assets/Sprites/Monsters/Zombie/rare.png";
static const std::string uniqueRarity_TexturePath = "Assets/Sprites/Monsters/Zombie/unique.png";
static const std::string all_TexturePaths[4] = { commonRarity_TexturePath, magicRarity_TexturePath, rareRarity_TexturePath, uniqueRarity_TexturePath };

Zombie::Zombie() : Zombie("Zombie") {};
Zombie::Zombie(std::string _name): Monster(_name) {
	renderer.AssignTexture(all_TexturePaths[(int)rarity]);
};