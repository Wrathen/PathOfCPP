#pragma once
#include "../Monster.h"
#include <string>

class Zombie : public Monster {
public:
	Zombie();
	Zombie(std::string name);

private:
	static std::string commonRarity_TexturePath;
	static std::string magicRarity_TexturePath;
	static std::string rareRarity_TexturePath;
	static std::string uniqueRarity_TexturePath;
};