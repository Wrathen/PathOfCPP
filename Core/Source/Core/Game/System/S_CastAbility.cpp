#include "S_CastAbility.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Entity/Entities.h"
#include "Core/Miscellaneous/Time.h"
#include "Core/Miscellaneous/Log.h"

void S_CastAbility::CastAbility(Core::Entity entity, const std::string& abilityName) {
	if (!entity.HasComponent<AbilitySystemComponent>())
		return;

	// Get the AbilitySystemComponent from the entity.
	auto& abilitySystem = entity.GetComponent<AbilitySystemComponent>();
	AbilityComponent* activeAbility = nullptr;

	// Check if we actually have the ability assigned to us.
	{
		bool isEligible = false;

		for (size_t i = 0; i < abilitySystem.abilities.size(); ++i) {
			if (abilitySystem.abilities[i] == abilityName) {
				isEligible = true;
				break;
			}
		}

		if (!isEligible) 
			return;
	}
	
	// Check if the target ability is already active.
	{
		for (size_t i = 0; i < abilitySystem.activeAbilities.size(); ++i) {
			if (abilitySystem.activeAbilities[i]->name == abilityName) {
				activeAbility = abilitySystem.activeAbilities[i];

				if (!activeAbility || activeAbility->uniqueInstance)
					return;

				break;
			}
		}
	}

	// Check cooldown eligibility.
	{
		if (Time::GetTime() < activeAbility->cooldownResetTime)
			return;
	}

	// Finally, if everything was OK so far, we should now be casting it.
	Internal_CastAbility(entity, abilityName);
}
void S_CastAbility::Internal_CastAbility(Core::Entity entity, const std::string& abilityName) {
	auto& abilitySystem = entity.GetComponent<AbilitySystemComponent>();
	AbilityComponent* abilityInstance = Internal_CreateAbilityInstance(abilityName);
	
	if (!abilityInstance) {
		Error("Ability Instance was not created properly in S_CastAbility.cpp");
		return;
	}
	
	abilitySystem.activeAbilities.push_back(abilityInstance);
}

AbilityComponent* S_CastAbility::Internal_CreateAbilityInstance(const std::string& abilityName) {
	Core::BaseScene* scene = Core::SceneMgr.GetCurrentScene();
	auto& reg = scene->reg;

	int abilityID = abilityDB[abilityName];
	switch (abilityID) {
		case 0: // Fireball
			// todo
			//Core::CreateProjectile(scene, )
			return new AbilityComponent{
				abilityID,
				abilityName,
				AbilityCostType::Mana,
				10.0f,
				0.5f,
				0,
				false
			};
		case 1: // Dash
			return new AbilityComponent{
				abilityID,
				abilityName,
				AbilityCostType::Mana,
				10.0f,
				0.5f,
				0,
				false
			};
		default:
			return nullptr;
	}
}