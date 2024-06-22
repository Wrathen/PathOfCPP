#pragma once
#include "Core/Game/Ability/Abilities.h"
#include "Core/Game/System/BaseSystem.h"
#include "Core/Game/Entity/Entity.h"

using namespace Core;
struct S_CastAbility : IBaseSystem {
	static void CastAbility(Entity* source, Entity* target, IAbilityPayload abilityPayload);

private:
	static void Internal_CastAbility(Entity* source, Entity* target, IAbilityPayload& abilityPayload);
};