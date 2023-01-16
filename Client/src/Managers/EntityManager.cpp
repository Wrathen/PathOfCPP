#include "EntityManager.h"
#include "CollisionManager.h"
#include "../Miscellaneous/Log.h"

void EntityManager::Update() {
	Collection::Update();
	
	for (auto& entity : *GetAll()) {
		entity->Update();
		entity->Render();
	}
}