#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	Entity CreateBaseNPC(BaseScene* scene, float posX, float posY) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		auto entity = reg.create();

		// Create In-Common Components.
		auto& C_EntityDetails = reg.emplace<EntityDetailsComponent>(entity, "BaseNPC", EntityType::NPC);
		auto& C_Transform = reg.emplace<TransformComponent>(entity, Vector2(posX, posY));

		// Create a Core::Entity and return it.
		return Entity(scene, entity);
	}

	Entity CreateMerchant(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Merchant specific components here.
		return entity;
	}
	Entity CreateGambler(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Gambler specific components here.
		return entity;
	}
	Entity CreateBlacksmith(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Blacksmith specific components here.
		return entity;
	}

	// Creates a random NPC in the current Scene.
	Entity CreateRandomNPC(BaseScene* scene, float x, float y) {
		auto randomType = RandomInt(0, 3);
		return (randomType == 0 ? CreateMerchant(scene, x, y) :
				randomType == 1 ? CreateGambler(scene, x, y) :
								  CreateBlacksmith(scene, x, y));
	}
}