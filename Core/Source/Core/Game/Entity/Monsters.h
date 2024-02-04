#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	inline Entity CreateBaseMonster(BaseScene* scene, float posX, float posY, unsigned int monsterLevel, unsigned int monsterID) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		Entity entity { scene, reg.create() };

		// Pick a random monster rarity
		MonsterRarity rarity = RandomEnum(MonsterRarity::Count);

		// Create In-Common Components.
		auto& C_EntityDetails = entity.AddComponent<EntityDetailsComponent>("BaseMonster", EntityType::Monster);
		auto& C_MonsterDetails = entity.AddComponent<MonsterDetailsComponent>(rarity, monsterID);
		auto& C_Stats = entity.AddComponent<StatsComponent>();
		entity.AddComponent<TransformComponent>(Vector2(posX, posY), Vector2((int)(rarity) * 0.40f + 2, (int)(C_MonsterDetails.rarity) * 0.40f + 2));
		entity.AddComponent<HealthComponent>(10.0f + RandomFloat(0.0f, ((int)rarity * 17.45f)));
		entity.AddComponent<BoxColliderComponent>();
		entity.AddComponent<MonsterAIComponent>();

		// Set-up component variables.
		C_Stats.level = monsterLevel;
		C_Stats.moveSpeed = 200.0f - ((int)rarity * 15.67f);

		// Return the new entity.
		return entity;
	}

	inline Entity CreateRandomBoar(BaseScene* scene, float posX, float posY, unsigned int monsterLevel) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, 1);
		// Add additional components that are specific to Boars.
		return entity;
	}
	inline Entity CreateRandomZombie(BaseScene* scene, float posX, float posY, unsigned int monsterLevel) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, 2);
		// Add additional components that are specific to Zombies.
		return entity;
	}

	inline Entity CreateRandomBreachMonster(BaseScene* scene, float posX, float posY, unsigned int monsterLevel, unsigned int monsterID) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, monsterID);

		// Add additional components that are specific to Breach Monsters.
		entity.AddComponent<BreachMonsterComponent>();

		return entity;
	}

	// Creates a random monster in the current Scene.
	inline Entity CreateRandomMonster(BaseScene* scene, float x, float y, unsigned int monsterLevel) {
		return (RandomInt(0, 2) ? CreateRandomBoar(scene, x, y, monsterLevel) : CreateRandomZombie(scene, x, y, monsterLevel));
	}
}