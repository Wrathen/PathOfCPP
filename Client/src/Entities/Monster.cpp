#include "Monster.h"

Monster::Monster() : Entity() {}
Monster::Monster(std::string name) : Entity(name) {}
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) {}