#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"
#include "Entity.h"

namespace Core {
	inline Entity CreateBasePlayer(BaseScene* scene, float posX, float posY) {
		// Create a new Entity.
		Entity entity { scene, scene->reg.create() };

		// Create In-Common Components.
		entity.AddComponent<EntityDetailsComponent>("BasePlayer", EntityType::Player);
		entity.AddComponent<PlayerComponent>();
		entity.AddComponent<TransformComponent>(Vector2(posX, posY), Vector2(2.2f, 2.2f));
		entity.AddComponent<StatsComponent>();
		entity.AddComponent<HealthComponent>(100.0f);
		entity.AddComponent<BoxColliderComponent>();
		auto& abilitySystem = entity.AddComponent<AbilitySystemComponent>();

		// Assign a few slots to abilities as default.
		abilitySystem.abilities[0] = "Fireball"; // Left click assigned to Fireball
		abilitySystem.abilities[4] = "Dash"; // E is assigned to Dash.

		// Return the new entity.
		return entity;
	}

	inline Entity CreatePlayer(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBasePlayer(scene, posX, posY);
		// Add additional components that are specific to players.
		return entity;
	}

	inline Entity CreatePortal(BaseScene* scene, float posX, float posY, uint32_t width, uint32_t height, const std::string& nextZone) {
		// Create a new Entity.
		Entity entity { scene, scene->reg.create() };

		// Create In-Common Components.
		entity.AddComponent<EntityDetailsComponent>(nextZone, EntityType::Portal);
		entity.AddComponent<PortalComponent>(nextZone);
		entity.AddComponent<TransformComponent>(Vector2(posX + width / 2 - 2000, posY + height / 2 - 2000));

		// Return the new entity.
		return entity;
	}

	inline Entity CreateProjectile(BaseScene* scene, float posX, float posY, float speed, float angle, uint64_t lifetime = 3000, int piercingAmount = 1, float damageAmount = 1) {
		// Create a new Entity.
		Entity entity { scene, scene->reg.create() };

		// Create In-Common Components.
		entity.AddComponent<EntityDetailsComponent>("BaseProj", EntityType::Projectile);
		entity.AddComponent<ProjectileComponent>();
		entity.AddComponent<TransformComponent>(Vector2(posX, posY), Vector2(1, 1), Vector2(speed * cos(angle), speed * sin(angle)));

		// Return the new entity.
		return entity;
	}
}