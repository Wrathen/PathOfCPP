#include "Entity.h"
#include "Game/Ability/Ability.h"
#include "Managers/EntityManager.h"
#include "Managers/GameManager.h"
#include "Managers/CollisionManager.h"

// Constructors
Entity::Entity(): Entity("Unnamed") {}
Entity::Entity(std::string _name) : Entity("Assets/Sprites/nosprite.png", _name) {}
Entity::Entity(std::string texturePath, std::string _name) {
	name = _name;

	EntityMgr.Add(this);
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);
	renderer.shouldDrawCentered = true;
}

// Main functions
void Entity::Update() {
	// Iterate over all active abilities and update them.
	for (auto* activeAbility : activeAbilities)
		activeAbility->Update();
}
void Entity::Render() { 
	renderer.Render();
	//GAME.DrawRect(transform.GetScreenPosition(), 15, 15);
}
void Entity::Delete() {
	if (isToBeDeleted) return;
	CollisionMgr.spatialHash.Remove(this);
	EntityMgr.Remove(this);
}

// Utility Functions
void Entity::AssignGUID(GUID _guid) {
	if (guid != 0)
		return;

	guid = _guid;
}
std::string Entity::ToString() {
	if (!this) return "This entity has already been deleted. What are you doing?!";
	return "Entity " + name + " with GUID: " + std::to_string(guid);
}

#pragma region Ability System
	void Entity::AddAbility(const std::string& abilityName) {
		// If we already have the ability, do not add it.
		if (HasAbility(abilityName))
			return;

		// Add the ability to the array.
		abilities.push_back(abilityName);
	}
	void Entity::RemoveAbility(const std::string& abilityName) {
		// Find the ability within the abilities vector.
		auto it = std::find(abilities.begin(), abilities.end(), abilityName);
		
		// If the given ability name couldn't be found, give an error message.
		if (it == abilities.end()) {
			Error("Ability couldn't be found!");
			return;
		}

		// Index of the ability within our vector
		uint32_t index = it - abilities.begin();

		RemoveAbility(index);
	}
	void Entity::RemoveAbility(uint32_t inputSlotID) {
		// First 7 indexes within the abilities vector is exclusive to input slots.
		if (inputSlotID < 7) {
			abilities[inputSlotID] = "";
			return;
		}

		// Check whether the parameter is within the bounds of our vector.
		if (inputSlotID >= abilities.size()) {
			Error("Given input slot ID is bigger than the given abilities array size!");
			return;
		}

		// Calculate the std::Iterator so we can erase it from the vector.
		auto it = abilities.begin() + inputSlotID;
		
		// Erase the ability from the vector.
		abilities.erase(it);
	}
	bool Entity::HasAbility(const std::string& abilityName) {
		// Get the iterator by the std function and check whether it points to the end of the vector.
		auto it = std::find(abilities.begin(), abilities.end(), abilityName);
		return it != abilities.end();
	}
	bool Entity::IsAbilityActive(const std::string& abilityName) {
		for (auto* ability : activeAbilities)
			if (ability->typeName == abilityName)
				return true;

		return false;
	}
	bool Entity::IsAbilityActive(uint32_t inputSlotID) {
		const std::string& abilityName = GetAbility(inputSlotID);
		return IsAbilityActive(abilityName);
	}
	void Entity::CastAbility(const std::string& abilityName) {
		// If the ability is already active, return.
		if (IsAbilityActive(abilityName)) return;

		// If we were able to cast the ability, then push it into our vector and start the ability.
		if (IAbility* ability = IAbility::CastAbility(this, abilityName)) {
			activeAbilities.push_back(ability);
			ability->Start();
		}
	}
	void Entity::CastAbility(uint32_t inputSlotID) { CastAbility(GetAbility(inputSlotID)); }
	void Entity::ActivateAbility(const std::string& abilityName) { CastAbility(abilityName); }
	void Entity::ActivateAbility(uint32_t inputSlotID) { CastAbility(inputSlotID); }
	void Entity::AssignAbilityToInputSlot(const std::string& abilityName, uint32_t inputSlotID) {
		// If the given input slot ID is faulty, give an error.
		if (inputSlotID >= 7) {
			Error("Input slot ID can only be between 0 and 6.");
			return;
		}

		// If we dont have the ability, give an error.
		if (!HasAbility(abilityName)) {
			Error("Specified ability has not been added to this entity. Why are you trying to assign it to an input slot?");
			return;
		}

		// Assign the given input slot ID to this new ability name.
		abilities[inputSlotID] = abilityName;
	}
	const std::string& Entity::GetAbility(uint32_t inputSlotID) {
		return abilities[inputSlotID];
	}
	IAbility* Entity::GetActiveAbility(const std::string& abilityName) {
		for (auto* ability : activeAbilities)
			if (ability->typeName == abilityName)
				return ability;

		return nullptr;
	}
	void Entity::CancelActiveAbility(const std::string& abilityName) {
		for (size_t i = 0; i < activeAbilities.size(); ++i) {
			IAbility* ability = activeAbilities[i];

			// Check whether the current lookup is the ability we seek, if so delete it and remove it from the vector.
			if (ability->typeName == abilityName) {
				auto it = activeAbilities.begin() + i;
				activeAbilities.erase(it);

				ability->Delete();
				return;
			}
		}

		Warn("Tried to cancel an ability that was not active!");
	}
	void Entity::CancelActiveAbility(IAbility* abilityInstance) {
		for (size_t i = 0; i < activeAbilities.size(); ++i) {
			IAbility* ability = activeAbilities[i];

			// Check whether the current lookup is the ability we seek, if so delete it and remove it from the vector.
			if (ability == abilityInstance) {
				auto it = activeAbilities.begin() + i;
				activeAbilities.erase(it);

				ability->Delete();
				return;
			}
		}

		Warn("Tried to cancel an ability instance that was not active!");
	}
#pragma endregion