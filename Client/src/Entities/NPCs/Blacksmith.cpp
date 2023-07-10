#include "Blacksmith.h"

Blacksmith::Blacksmith(std::string name): 
	NPC("assets/sprites/monsters/115.png", "Blacksmith " + name) 
{
	renderer.SetScale(0.05f, 0.05f);
};