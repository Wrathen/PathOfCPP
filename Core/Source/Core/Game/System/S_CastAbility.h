#pragma once
#include <string>
#include "Core/Game/Component/Components.h"
#include "Core/Game/System/BaseSystem.h"
#include "Core/Game/Entity/Entity.h"

struct S_CastAbility : Core::IBaseSystem {
	void CastAbility(Core::Entity entity, const std::string& abilityName);

private:
	// [Temp]
	std::unordered_map<std::string, int> abilityDB {
		{ "Fireball", 0 },
		{ "Dash", 1 }
	};

	void Internal_CastAbility(Core::Entity entity, const std::string& abilityName);
	AbilityComponent* Internal_CreateAbilityInstance(const std::string& abilityName);
};