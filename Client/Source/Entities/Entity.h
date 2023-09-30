#pragma once
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"
#include "../Miscellaneous/UtilityMacros.h"

enum class EntityFlags {
	NONE = 0,
	IsPlayer = 1,
	IsMonster = 2,
	IsNPC = 4,
	IsHittable = 8,
	IsBreachLeagueSpecific = 16,
	IsHostile = 32
};
DEFINE_FLAG_OPERATORS(EntityFlags)

class Entity {
public:
	// Generic Variables
	std::string name;
	GUID guid = 0;
	EntityFlags flags = EntityFlags::NONE; // A flag for bunch of entity specific information.

	bool isToBeDeleted = false; // Boolean that marks an entity for deletion on late-update.
	bool isToBeDeletedOnSceneChange = true; // Boolean that marks an entity for deletion on scene changes.
	bool isAutoUpdateEnabled = true; // Toggle automatic Update() calls to this entity. Disable for manual Update() calls.

	// Enforced Components
	Transform transform;
	SpriteRenderer renderer;
	
	// Constructors & Deconstructors
	Entity();
	Entity(std::string name);
	Entity(std::string texturePath, std::string name);
	virtual ~Entity() = default;

	// Base Functions
	virtual void Start() = 0;
	virtual void Update();
	virtual void Render();

	// Main Functions
	void Delete();

	// Events
	virtual void OnKill() = 0;
	virtual void OnDeath() = 0;

	// Utility Functions
	void AssignGUID(GUID _guid);
	virtual std::string ToString();

#pragma region ECS
	public:
		template <typename T>
		T* AddComponent() {
			T* component = new T();
			component->SetSource(this);
			component->Start();
			allComponents[std::type_index(typeid(T))] = component;
			return component;
		}

		template <typename T>
		T* GetComponent() {
			auto it = allComponents.find(std::type_index(typeid(T)));
			if (it == allComponents.end()) return nullptr;
			return static_cast<T*>(it->second);
		}

	private:
		std::unordered_map<std::type_index, void*> allComponents;
#pragma endregion

#pragma region Ability System
	private:
		/* 
		*	Vector of all added abilities to this entity.
		*
		*	Vector indexes are used as "Input Slot ID".
		*	[0] = LMB, [1] = RMB, [2] = Q, [3] = W, [4] = E, [5] = R, [6] = T
		*
		*   First 7 indexes are reserved and can be empty strings.
		*   Rest of the indexes are abilities that are given and can be activated without the usage of inputs.
		*/
		std::vector<std::string> abilities { "", "", "", "", "", "", "" };
		
		// Vector of all currently active ability instances by this entity.
		std::vector<class IAbility*> activeAbilities;
	
	public:
		// Returns all added abilities to this entity.
		const std::vector<std::string>& GetAbilities() { return abilities; }
		// Returns all active abilities by this entity.
		const std::vector<IAbility*>& GetActiveAbilities() { return activeAbilities; }

protected:
		// Adds an ability to this entity by ability name.
		void AddAbility(const std::string& abilityName);

		// Removes an ability from this entity by ability name.
		void RemoveAbility(const std::string& abilityName);

		// Removes an ability from this entity by input slot ID.
		void RemoveAbility(uint32_t inputSlotID);

		// Returns boolean whether the specified ability is added to the entity.
		bool HasAbility(const std::string& abilityName);

		// Returns boolean whether the specified ability is active by ability name.
		bool IsAbilityActive(const std::string& abilityName);

		// Returns boolean whether the specified ability is active by input slot ID.
		bool IsAbilityActive(uint32_t inputSlotID);

		// Casts an ability by name. CastAbility and ActivateAbility are LITERALLY the same thing.
		void CastAbility(const std::string& abilityName);

		// Casts an ability by input slot ID. CastAbility and ActivateAbility are LITERALLY the same thing.
		void CastAbility(uint32_t inputSlotID);

		// Activates an ability by name. CastAbility and ActivateAbility are LITERALLY the same thing.
		void ActivateAbility(const std::string& abilityName);

		// Activates an ability by input slot ID. CastAbility and ActivateAbility are LITERALLY the same thing.
		void ActivateAbility(uint32_t inputSlotID);

		/* 
		*	Assigns an ability to a given input slot.
		**  [WARNING] Ability has to already be added to the entity! **
		*/
		void AssignAbilityToInputSlot(const std::string& abilityName, uint32_t inputSlotID);

		// Retrieves an added ability's name by input slot ID.
		const std::string& GetAbility(uint32_t inputSlotID);

		// Retrieves an active ability instance by name.
		IAbility* GetActiveAbility(const std::string& abilityName);

		// Cancels an active ability by ability name. This also removes and deletes the ability. (ref IAbility::Delete)
		void CancelActiveAbility(const std::string& abilityName);

public:
		// Cancels an active ability by pointer to the ability instance. This also removes and deletes the ability. (ref IAbility::Delete)
		void CancelActiveAbility(IAbility* abilityInstance);
#pragma endregion
};