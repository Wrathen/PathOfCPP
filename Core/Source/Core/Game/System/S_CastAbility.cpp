#include "S_CastAbility.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Entity/Entities.h"
#include "Core/Miscellaneous/Time.h"
#include "Core/Miscellaneous/Log.h"
#include "Core/Miscellaneous/ErrorHandler.h"

void S_CastAbility::CastAbility(Entity* source, Entity* target, IAbilityPayload abilityPayload) {
	if (!source->HasComponent<AbilitySystemComponent>())
		return;

	// Get the AbilitySystemComponent from the entity.
	auto& abilitySystem = source->GetComponent<AbilitySystemComponent>();
	IAbilityInstance* activeAbility = nullptr;
	int32_t abilityID = abilityPayload.read<int32_t>(true);

	// Check if we actually have the ability assigned to us.
	{
		bool isEligible = false;

		for (size_t i = 0; i < abilitySystem.abilities.size(); ++i) {
			if (abilitySystem.abilities[i] == abilityID) {
				isEligible = true;
				break;
			}
		}

		if (!isEligible) 
			return;
	}
	
	// Enforce UniqueInstance. Check if the target ability is already active.
	{
		for (size_t i = 0; i < abilitySystem.activeAbilities.size(); ++i) {
			if (abilitySystem.activeAbilities[i]->ID == abilityID) {
				activeAbility = abilitySystem.activeAbilities[i];

				if (activeAbility->uniqueInstance)
					return;

				break;
			}
		}
	}

	// Check cooldown eligibility.
	{
		if (activeAbility && Time::GetTimeMS() < activeAbility->cooldownResetTime)
			return;
	}

	// Finally, if everything was OK so far, we should now be casting it.
	Internal_CastAbility(source, target, abilityPayload);
}
void S_CastAbility::Internal_CastAbility(Entity* source, Entity* target, IAbilityPayload& abilityPayload) {
	auto& abilitySystem = source->GetComponent<AbilitySystemComponent>();
	int32_t abilityID = abilityPayload.read<int32_t>(true);
	IAbilityInstance* abilityInstance = nullptr;

	switch (abilityID)
	{
		case 0:
			abilitySystem.activeAbilities.emplace_back(new A_Fireball(abilityPayload));
			break;
		case 1:
			abilitySystem.activeAbilities.emplace_back(new A_Dash(abilityPayload));
			break;
		default:
			Error("Ability Instance was not created properly in S_CastAbility.cpp");
			return;
	}

	abilityInstance = abilitySystem.activeAbilities.back();
	abilityInstance->Init(source, target);

	// If we have an on begin function defined, lets call it here.
	if (abilityInstance->onBegin)
		abilityInstance->onBegin();
}