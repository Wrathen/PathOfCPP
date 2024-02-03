#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	Entity CreateBaseMonster(BaseScene* scene, float posX, float posY, unsigned int monsterLevel, unsigned int monsterID) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		auto entity = reg.create();

		// Pick a random monster rarity
		MonsterRarity rarity = RandomEnum(MonsterRarity::Count);

		// Create In-Common Components.
		auto& C_EntityDetails = reg.emplace<EntityDetailsComponent>(entity, "BaseMonster", EntityType::Monster);
		auto& C_MonsterDetails = reg.emplace<MonsterDetailsComponent>(entity, rarity, monsterID);
		auto& C_Stats = reg.emplace<StatsComponent>(entity);
		reg.emplace<TransformComponent>(entity, Vector2(posX, posY), Vector2((int)(rarity) * 0.40f + 2, (int)(C_MonsterDetails.rarity) * 0.40f + 2));
		reg.emplace<HealthComponent>(entity, 10.0f + RandomFloat(0.0f, ((int)rarity * 17.45f)));
		reg.emplace<BoxColliderComponent>(entity);

		// Set-up component variables.
		C_Stats.level = monsterLevel;
		C_Stats.moveSpeed = 200.0f - ((int)rarity * 15.67f);

		// Create a Core::Entity and return it.
		return Entity(scene, entity);
	}

	Entity CreateRandomBoar(BaseScene* scene, float posX, float posY, unsigned int monsterLevel) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, 1);
		// Add additional components that are specific to Boars.
		return entity;
	}
	Entity CreateRandomZombie(BaseScene* scene, float posX, float posY, unsigned int monsterLevel) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, 2);
		// Add additional components that are specific to Zombies.
		return entity;
	}

	Entity CreateRandomBreachMonster(BaseScene* scene, float posX, float posY, unsigned int monsterLevel, unsigned int monsterID) {
		Entity entity = CreateBaseMonster(scene, posX, posY, monsterLevel, monsterID);

		// Add additional components that are specific to Breach Monsters.
		entity.AddComponent<BreachMonsterComponent>();

		return entity;
	}

	// Creates a random monster in the current Scene.
	Entity CreateRandomMonster(BaseScene* scene, float x, float y, unsigned int monsterLevel) {
		return (RandomInt(0, 2) ? CreateRandomBoar(scene, x, y, monsterLevel) : CreateRandomZombie(scene, x, y, monsterLevel));
	}
}