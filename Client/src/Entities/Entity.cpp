#include "Entity.h"
#include "../Managers/EntityManager.h"

Entity::Entity(): Entity("Unnamed") {}
Entity::Entity(std::string _name) : Entity("assets/sprites/nosprite.png", _name) {}
Entity::Entity(std::string texturePath, std::string _name) {
	name = _name;

	EntityMgr.AddEntity(this);
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);
	renderer.shouldDrawCentered = true;
}

void Entity::Render() { renderer.Render(); }
void Entity::Delete() { EntityMgr.RemoveEntity(this); }