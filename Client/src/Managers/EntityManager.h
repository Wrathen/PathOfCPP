#pragma once
#include "../Entities/Entity.h"
#include <unordered_map>
#include <vector>

#define EntityMgr EntityManager::GetInstance()
class EntityManager {
public:
    static EntityManager& GetInstance() {
        static EntityManager instance;
        return instance;
    }

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    Entity* GetEntity(GUID guid);

    void PrintAllEntities();
    void UpdateAllEntities();
    void RenderAllEntities();
    auto GetAllEntities() { return &entityList; }

private:
    EntityManager() {}
    ~EntityManager();
    EntityManager(EntityManager const&) = delete;
    void operator=(EntityManager const&) = delete;

    void DeleteEntity(Entity* entity);
    void DeleteAllQueuedEntities();

private:
    std::unordered_map<GUID, Entity*> entityList;
    std::vector<Entity*> toBeDeletedList;
};