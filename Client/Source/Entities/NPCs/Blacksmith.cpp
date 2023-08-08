#include "Blacksmith.h"

Blacksmith::Blacksmith(std::string name): 
	NPC("Assets/Sprites/Monsters/115.png", "Blacksmith " + name) 
{
	renderer.SetScale(0.05f, 0.05f);
};