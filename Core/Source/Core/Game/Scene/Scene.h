#pragma once
#include <memory>
#include <entt.hpp>
#include "Core/Game/Zone/Zone.h"
#include "Core/Game/System/BaseSystem.h"

namespace Core {
	struct BaseScene {
		// All entities and components live inside this ent::registry object.
		entt::registry reg;

		// All Players vector for quick access.
		std::vector<entt::entity> players;

		// All the systems concurrent in the scene.
		std::vector<std::shared_ptr<IBaseSystem>> activeSystems;

		// Generic Variables
		std::string name = std::string();
		std::string zoneDataPath = std::string();
		int totalNumberOfSpawnedNPCs = 0;
		int totalNumberOfSpawnedMonsters = 0;
		int totalNumberOfSpawnedPlayers = 0;
		unsigned int monsterLevel = 1;

		// Constructors
		BaseScene();
		BaseScene(const std::string& _zoneDataPath);
		BaseScene(const std::string& _zoneDataPath, const std::string& _name);

		// Base Functions
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Clear();

		template <typename SystemType>
		IBaseSystem* AddSystem() {
			auto& newSystem = activeSystems.emplace_back(std::make_shared<SystemType>());
			newSystem.get()->Start();
			return newSystem.get();
		}

		// Main Functions
		virtual entt::entity SpawnEntity();
		virtual entt::entity SpawnPlayer(float posX, float posY);
		virtual entt::entity SpawnNPC(float posX, float posY, int type);
		virtual entt::entity SpawnMonster(float posX, float posY);
		virtual entt::entity SpawnMonsterInZone(const ZoneSpawnZoneData& zone);

	protected:
		std::vector<ZoneEntityData> entities;
		std::vector<ZoneSpawnZoneData> spawnZones;

		virtual void LoadZone();
		virtual void AddNPCs(const std::vector<ZoneEntityData>& entityData);
		virtual void AddSpawnZones(const std::vector<ZoneSpawnZoneData>& spawnZoneData);
		virtual void AddPortals(const std::vector<ZonePortalData>& portalData);
		virtual void AddStaticColliders(const std::vector<ZoneColliderData>& colliderData);
		void Reset();

	public:
		// Getters && Setters
		int GetMonsterLevel() { return monsterLevel; }
		void SetMonsterLevel(unsigned int value) { monsterLevel = value; }
	};
}