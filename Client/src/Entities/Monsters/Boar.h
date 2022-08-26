#pragma once
#include "../Monster.h"
#include <string>

class Boar : public Monster {
public:
	Boar();
	Boar(std::string name);

private:
	static std::string commonRarity_TexturePath;
	static std::string magicRarity_TexturePath;
	static std::string rareRarity_TexturePath;
	static std::string uniqueRarity_TexturePath;
};