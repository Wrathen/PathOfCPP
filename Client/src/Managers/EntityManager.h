#pragma once
#include <unordered_map>
#include "../Entities/Entity.h"

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

private:
    EntityManager() {}
    ~EntityManager();
    EntityManager(EntityManager const&) = delete;
    void operator=(EntityManager const&) = delete;

private:
    std::unordered_map<GUID, Entity*> entityList;
};