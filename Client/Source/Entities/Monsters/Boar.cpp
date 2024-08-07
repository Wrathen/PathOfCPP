#include "Boar.h"
#include "../../Miscellaneous/Random.h"

// [To-Do] 
// After you implement a Shader class, dump these and switch to using a simple shader color outlining the sprite.
static const std::string commonRarity_TexturePath = "Assets/Sprites/Monsters/Boar/common.png";
static const std::string magicRarity_TexturePath = "Assets/Sprites/Monsters/Boar/magic.png";
static const std::string rareRarity_TexturePath = "Assets/Sprites/Monsters/Boar/rare.png";
static const std::string uniqueRarity_TexturePath = "Assets/Sprites/Monsters/Boar/unique.png";
static const std::string all_TexturePaths[4] = { commonRarity_TexturePath, magicRarity_TexturePath, rareRarity_TexturePath, uniqueRarity_TexturePath };

Boar::Boar() : Boar("Boar") {};
Boar::Boar(std::string name) : Monster(name) {
	renderer.AssignTexture(all_TexturePaths[(int)rarity]);
};