#include "EntityManager.h"


void EntityManager::Update() {
	Collection::Update();

	for (auto& entity : *GetAll()) {
		entity.second->Update();
		entity.second->Render();
	}
}