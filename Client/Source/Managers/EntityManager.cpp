#include "EntityManager.h"
#include "CollisionManager.h"
#include "../Miscellaneous/Log.h"

void EntityManager::Update() {
	for (auto& entity : GetAll()) {
		if (!GAME.isGamePaused && entity->isAutoUpdateEnabled) entity->Update();
		entity->Render();
	}
}
void EntityManager::UpdateCollection() { Collection::Update(); }

std::vector<Entity*> EntityManager::FindAll(EntityFlags flags) {
	std::vector<Entity*> foundEntities;

	for (auto& entity: GetAll())
		if (!entity->isToBeDeleted && entity->flags & flags)
			foundEntities.emplace_back(entity.get());

	return foundEntities;
}
