#pragma once
#include <string>
#include <unordered_map>

// This is the base Interface Ability class that each ability should derive from.
class IAbility {
public:
	// Enforced member variable Caster and Constructor
	class Entity* caster = nullptr;
	IAbility(Entity* _caster) : caster(_caster) {}

	// Base Interface Functions that has to be overridden by derived classes.
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Delete() = 0;

	// Below is the list of the all available abilities in the game that can be activated.
	static std::unordered_map<std::string, uint32_t> AbilityList;

	// Static functions
	static void CastAbility(Entity* caster, const std::string& abilityName);
	static void CastAbility(Entity* caster, uint32_t abilityID);
};