#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"
#include "Entity.h"

namespace Core {
	Entity CreateBasePlayer(BaseScene* scene, float posX, float posY) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		auto entity = reg.create();

		// Create In-Common Components.
		reg.emplace<EntityDetailsComponent>(entity, "BasePlayer", EntityType::Player);
		reg.emplace<PlayerComponent>(entity);
		reg.emplace<TransformComponent>(entity, Vector2(posX, posY), Vector2(2.2f, 2.2f));
		reg.emplace<StatsComponent>(entity);
		reg.emplace<HealthComponent>(entity, 100.0f);
		reg.emplace<BoxColliderComponent>(entity);
		auto& abilitySystem = reg.emplace<AbilitySystemComponent>(entity);

		// Assign a few slots to abilities as default.
		abilitySystem.abilities[0] = "Fireball"; // Left click assigned to Fireball
		abilitySystem.abilities[4] = "Dash"; // E is assigned to Dash.

		// Create a Core::Entity and return it.
		return Entity(scene, entity);
	}

	Entity CreatePlayer(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBasePlayer(scene, posX, posY);
		// Add additional components that are specific to players.
		return entity;
	}

	Entity CreatePortal(BaseScene* scene, float posX, float posY, uint32_t width, uint32_t height, const std::string& nextZone) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		auto entity = reg.create();

		// Create In-Common Components.
		auto& C_EntityDetails = reg.emplace<EntityDetailsComponent>(entity, nextZone, EntityType::Portal);
		auto& C_Portal = reg.emplace<PortalComponent>(entity, nextZone);
		auto& C_Transform = reg.emplace<TransformComponent>(entity, Vector2(posX + width / 2 - 2000, posY + height / 2 - 2000));

		// Create a Core::Entity and return it.
		return Entity(scene, entity);
	}

	Entity CreateProjectile(BaseScene* scene, float posX, float posY, float speed, float angle, uint64_t lifetime = 3000, int piercingAmount = 1, float damageAmount = 1) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		auto entity = reg.create();

		// Create In-Common Components.
		auto& C_EntityDetails = reg.emplace<EntityDetailsComponent>(entity, "BaseProj", EntityType::Projectile);
		auto& C_Projectile = reg.emplace<ProjectileComponent>(entity);
		auto& C_Transform = reg.emplace<TransformComponent>(entity, Vector2(posX, posY), Vector2(1, 1), Vector2(speed * cos(angle), speed * sin(angle)));

		// Create a Core::Entity and return it.
		return Entity(scene, entity);
	}
}