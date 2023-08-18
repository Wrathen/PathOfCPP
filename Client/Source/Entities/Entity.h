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
	std::string name;
	GUID guid = 0;

	Transform transform;
	SpriteRenderer renderer;
	EntityFlags flags = EntityFlags::NONE;

	bool isToBeDeleted = false;
	bool isToBeDeletedOnSceneChange = true;
	bool isAutoUpdateEnabled = true;

	// Constructors & Deconstructors
	Entity();
	Entity(std::string name);
	Entity(std::string texturePath, std::string name);
	virtual ~Entity() = default;

	// Base Functions
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render();

	// Main Functions
	void Delete();

	// Events
	virtual void OnKill() = 0;
	virtual void OnDeath() = 0;

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString();

	// ECS
	template <typename T>
	T* AddComponent() {
		T* component = new T();
		component->SetSource(this);
		component->Start();
		components_[std::type_index(typeid(T))] = component;
		return component;
	}

	template <typename T>
	T* GetComponent() {
		auto it = components_.find(std::type_index(typeid(T)));
		if (it == components_.end()) return nullptr;
		return static_cast<T*>(it->second);
	}

private:
	std::unordered_map<std::type_index, void*> components_;
};