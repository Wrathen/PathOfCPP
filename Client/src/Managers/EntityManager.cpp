#include "EntityManager.h"
#include <string>
#include "../Miscellaneous/Log.h"

// Main Functions
void EntityManager::AddEntity(Entity* entity) {
	if (entity == nullptr) return;

	static GUID guid;
	entity->AssignGUID(guid);
	entityList[guid++] = entity;
}
void EntityManager::RemoveEntity(Entity* entity) { 
	if (!entity) return;
	toBeDeletedList.push_back(entity);
	entity->isToBeDeleted = true;
}
void EntityManager::DeleteEntity(Entity* entity) {
	if (!entity) return;

	//Debug("Deleted " + entity->ToString());
	entityList.erase(entity->guid);

	delete entity;
}
Entity* EntityManager::GetEntity(GUID guid) {
	auto entity = entityList.find(guid);
	return entity != entityList.end() ? entity->second : nullptr;
}

// Main Loop&Utility
void EntityManager::DeleteAllQueuedEntities() {
	for (auto it = toBeDeletedList.rbegin(); it != toBeDeletedList.rend(); ++it) DeleteEntity(*it);
	toBeDeletedList.clear();
}
void EntityManager::PrintAllEntities() {
	for (auto& entity : entityList)
		Debug(entity.second->ToString());
}
void EntityManager::UpdateAllEntities() {
	DeleteAllQueuedEntities();

	for (auto& entity : entityList)
		entity.second->Update();
}
void EntityManager::RenderAllEntities() {
	for (auto& entity : entityList)
		entity.second->Render();
}

EntityManager::~EntityManager() {
	for (auto& entity : entityList) delete entity.second;
	entityList.clear();
}