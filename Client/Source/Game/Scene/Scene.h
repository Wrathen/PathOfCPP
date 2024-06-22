#pragma once
#include "Core/Game/Scene/Scene.h"

struct Scene : public Core::BaseScene {
	// Base Functions
	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Clear() override;

	// Main Functions
	void AddBackground();

	entt::entity SpawnPlayer(float posX, float posY) override;
	entt::entity SpawnNPC(float posX, float posY, int type) override;
	entt::entity SpawnProjectile(float posX, float posY, float speed, float angle, uint64_t lifetime = 3000, int piercingAmount = 1, float damageAmount = 1) override;
	entt::entity SpawnMonster(float posX, float posY) override;
	entt::entity SpawnMonsterInZone(const Core::ZoneSpawnZoneData& zone) override;

	// Constructors
	Scene();
	Scene(const std::string& _zoneDataPath);
	Scene(const std::string& _zoneDataPath, const std::string& _name);

private:
	void LoadZone() override;
};