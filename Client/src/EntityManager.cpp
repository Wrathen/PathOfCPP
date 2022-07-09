#include "EntityManager.h"
#include "GameManager.h"
#include <string>

void EntityManager::AddEntity(Entity* entity) {
    if (entity == nullptr) return;

    static unsigned int guid;
    entity->AssignGUID(guid);
    entityList[guid++] = entity;
}
void EntityManager::RemoveEntity(Entity* entity) {
    if (entity == nullptr) return;

    GAME.Debug("Deleting " + entity->ToString());
    GAME.Debug("Deleted " + std::to_string(entityList.erase(entity->guid)) + " entities.");
    delete entity;
}

Entity* EntityManager::GetEntity(GUID guid) {
    auto entity = entityList.find(guid);
    return entity != entityList.end() ? entity->second : nullptr;
}

void EntityManager::PrintAllEntities() {
    for (auto& entity : entityList)
        GAME.Debug(entity.second->ToString());
}

EntityManager::~EntityManager() {
    for (auto& entity : entityList) delete entity.second;
    entityList.clear();
}