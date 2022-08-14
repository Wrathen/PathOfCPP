#include "Entity.h"
#include "../Managers/EntityManager.h"

Entity::Entity() { EntityMgr.AddEntity(this); renderer.AssignTransform(&transform); Start(); }
Entity::Entity(std::string _name) : Entity() { name = _name; }
Entity::Entity(std::string texturePath, std::string _name) : Entity(_name) { renderer.AssignTexture(texturePath); }

void Entity::Delete() { EntityMgr.RemoveEntity(this); }

void Entity::Start() {}
void Entity::Update() {
    if (++transform.position.x > 800) {
        if (++transform.position.y > 600) transform.position.y = 0;
        transform.position.x = 0;
    }
    ++transform.rotation;
}
void Entity::Render() { renderer.Render(); }