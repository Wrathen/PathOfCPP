#include "EntityManager.h"

void EntityManager::Update() {
	Collection::Update();
}
void EntityManager::RenderAll() {
	auto* entityList = GetAll();
	for (auto entity : *entityList)
		entity.second->Render();
} 