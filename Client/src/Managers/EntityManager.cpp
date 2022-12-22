#include "EntityManager.h"


void EntityManager::Update() {
	Collection::Update();

	for (auto& entity : *GetAll())
		entity.second->Update();
}
void EntityManager::RenderAll() {
	for (auto& entity : *GetAll())
		entity.second->Render();
} 