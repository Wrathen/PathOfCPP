#include "S_GCAbilityInstances.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Ability/Abilities.h"
#include <Core/Miscellaneous/Time.h>

void S_GCAbilityInstances::Update()
{
	auto& reg = Core::SceneMgr.GetCurrentScene()->reg;
	auto view = reg.view<AbilitySystemComponent>();

	// Delete Ability Instances
	view.each([&reg](auto entity, AbilitySystemComponent& abilitySystem) {
		std::vector<IAbilityInstance*>& vector = abilitySystem.activeAbilities;
		auto currentTime = Time::GetTimeMS();

		for (auto it = vector.begin(); it != vector.end();)
		{
			if (currentTime > (*it)->deathTime)
			{
				delete (*it);
				it = vector.erase(it);
			}
			else ++it;
		}
	});
}