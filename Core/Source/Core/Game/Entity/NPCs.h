#pragma once
#include <entt.hpp>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	inline Entity CreateBaseNPC(BaseScene* scene, float posX, float posY) {
		// Retrieve the registry.
		auto& reg = scene->reg;

		// Create a new Entity.
		Entity entity { scene, reg.create() };

		// Create In-Common Components.
		auto& C_EntityDetails = entity.AddComponent<EntityDetailsComponent>("BaseNPC", EntityType::NPC);
		auto& C_Transform = entity.AddComponent<TransformComponent>(Vector2(posX, posY));

		// Return the new entity.
		return entity;
	}

	inline Entity CreateMerchant(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Merchant specific components here.
		return entity;
	}
	inline Entity CreateGambler(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Gambler specific components here.
		return entity;
	}
	inline Entity CreateBlacksmith(BaseScene* scene, float posX, float posY) {
		Entity entity = CreateBaseNPC(scene, posX, posY);
		// Add Blacksmith specific components here.
		return entity;
	}

	// Creates a random NPC in the current Scene.
	inline Entity CreateRandomNPC(BaseScene* scene, float x, float y) {
		auto randomType = RandomInt(0, 3);
		return (randomType == 0 ? CreateMerchant(scene, x, y) :
				randomType == 1 ? CreateGambler(scene, x, y) :
								  CreateBlacksmith(scene, x, y));
	}
}