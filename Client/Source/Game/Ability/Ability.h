#pragma once
#include <string>
#include <unordered_map>

// This is the base Interface Ability class that each ability should derive from.
class IAbility {
public:
	// Member Variables
	class Entity* caster = nullptr;
	std::string typeName = "Unnamed Ability";

	// Constructor
	IAbility(Entity* _caster, const std::string& _typeName) : caster(_caster), typeName(_typeName) {}

	// Base Interface Functions that has to be overridden by derived classes.
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Delete() = 0;

	// Below is the list of the all available abilities in the game that can be activated.
	static std::unordered_map<std::string, uint32_t> AbilityList;

	// Static functions
	static IAbility* CastAbility(Entity* caster, const std::string& abilityName);
	static IAbility* CastAbility(Entity* caster, uint32_t abilityID);
};