#pragma once
#include <unordered_map>
#include <vector>
#include "../Entities/Entity.h"
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Collection.h"

#define EntityMgr EntityManager::GetInstance()
class EntityManager : public Collection<Entity>, public Singleton<EntityManager> { friend class Singleton;
public:
    void Update();

	EntityManager() = delete;

	// copy ctor
	EntityManager(EntityManager const&) = delete;
	// move ctor
	EntityManager(EntityManager&&) = delete;
	// assignment op overload
	EntityManager& operator=(EntityManager const&) = delete;

private:
	EntityManager() : Collection<Entity>(100000) {}
};