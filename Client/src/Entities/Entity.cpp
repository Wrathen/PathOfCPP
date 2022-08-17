#include "Entity.h"
#include "../Managers/EntityManager.h"

Entity::Entity() { EntityMgr.AddEntity(this); renderer.AssignTransform(&transform); Start(); }
Entity::Entity(std::string _name) : Entity() { name = _name; }
Entity::Entity(std::string texturePath, std::string _name) : Entity(_name) { renderer.AssignTexture(texturePath); }

void Entity::Delete() { EntityMgr.RemoveEntity(this); }

void Entity::Start() {}
void Entity::Update() {}
void Entity::Render() { renderer.Render(); }