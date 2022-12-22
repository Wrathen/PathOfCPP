#pragma once
#include <unordered_map>
#include <vector>
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Collection.h"
#include "../Components/Collision/Collider.h"
#include "../Components/Collision/SpatialHash.h"

#define CollisionMgr CollisionManager::GetInstance()
class CollisionManager : public Collection<Collider>, public Singleton<CollisionManager> { friend class Singleton;
public:
	SpatialHash spatialHash{ GAME.gameWidth * 2, GAME.gameHeight * 2, 160 };

	void ResetSpatialHash();
	void Update();

private:
	CollisionManager() {}
	~CollisionManager() {}
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
};