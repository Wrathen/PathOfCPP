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

private:
	EntityManager() {}
	~EntityManager() {}
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;
};