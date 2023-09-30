#include "Ability.h"
#include "Miscellaneous/Log.h"
#include "ShootArrow.h"
#include "Fireball.h"
#include "Dash.h"

// Initialize the static map of ALL the abilities.
std::unordered_map<std::string, uint32_t> IAbility::AbilityList {
	{ "ShootArrow", 0 },
	{ "Fireball", 1 },
	{ "Dash", 2 }
};

// Cast an ability by the Ability Name.
void IAbility::CastAbility(Entity* caster, const std::string& abilityName) {
	// Find the AbilityID by AbilityName
	auto it = AbilityList.find(abilityName);
	uint32_t abilityID = it == AbilityList.end() ? -1 : it->second;

	CastAbility(caster, abilityID);
}

// Cast an ability by the Ability ID.
void IAbility::CastAbility(Entity* caster, uint32_t abilityID) {
	// Check if the specified abilityName has been registered above.
	if (abilityID == -1) {
		Error("Desired ability couldn't be found. Check Ability.h");
		return;
	}

	// Check if the caster is valid.
	if (!caster) {
		Error("No caster found in the function CastAbility.");
		return;
	}

	// Switch on the AbilityID and create an instance of the desired ability class.
	IAbility* createdAbility;
	switch (abilityID) {
	case 0:
		createdAbility = new ShootArrow(caster);
		break;
	case 1:
		createdAbility = new Fireball(caster);
		break;
	case 2:
		createdAbility = new Dash(caster);
		break;
	default:
		Error("Specified ability is not found in the database. Check Ability.h");
		return;
	}

	createdAbility->Start();
}