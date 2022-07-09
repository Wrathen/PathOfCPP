#include "Entity.h"
#include "EntityManager.h"

Entity::Entity() { EntityMgr.AddEntity(this); }
Entity::Entity(std::string name) { EntityMgr.AddEntity(this); this->name = name; }

void Entity::Delete() { EntityMgr.RemoveEntity(this); }
std::string Entity::ToString() {
    if (!this) return "This entity has already been deleted. What are you doing?!";
    return "Entity " + name + " with GUID: " + std::to_string(guid);
}