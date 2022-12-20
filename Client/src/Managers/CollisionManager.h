#pragma once
#include <unordered_map>
#include <vector>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Collection.h"
#include "../Components/Collision/Collider.h"

#define CollisionMgr CollisionManager::GetInstance()
class CollisionManager : public Collection<Collider>, public Singleton<CollisionManager> { friend class Singleton;
public:
	void Update();

private:
	CollisionManager() {}
	~CollisionManager() {}
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
};