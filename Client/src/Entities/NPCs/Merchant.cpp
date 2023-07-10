#include "Merchant.h"

Merchant::Merchant(std::string name): 
	NPC("assets/sprites/monsters/146.png", "Merchant " + name) 
{
	renderer.SetScale(0.05f, 0.05f);
};