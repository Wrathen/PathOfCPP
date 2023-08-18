#include "Entity.h"
#include "../Managers/EntityManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/CollisionManager.h"

Entity::Entity(): Entity("Unnamed") {}
Entity::Entity(std::string _name) : Entity("Assets/Sprites/nosprite.png", _name) {}
Entity::Entity(std::string texturePath, std::string _name) {
	name = _name;

	EntityMgr.Add(this);
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);
	renderer.shouldDrawCentered = true;
}
void Entity::Render() { 
	renderer.Render();
	//GAME.DrawRect(transform.GetScreenPosition(), 15, 15);
}

// Main functions
void Entity::Delete() {
	if (isToBeDeleted) return;
	CollisionMgr.spatialHash.Remove(this);
	EntityMgr.Remove(this);
}

// Utility Functions
std::string Entity::ToString() {
	if (!this) return "This entity has already been deleted. What are you doing?!";
	return "Entity " + name + " with GUID: " + std::to_string(guid);
}