#pragma once
#include <string>
#include "../Components/Stats.h"
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

class Entity {
	friend class EntityManager;
public:
	Entity();
	Entity(std::string name);
	Entity(std::string texturePath, std::string name);

	// Base Functions
	virtual void Start();
	virtual void Update();
	virtual void Render();

	// Main Functions
	void Delete();
	virtual Stats* GetStats() { return nullptr; }

	// Utility Functions
	virtual std::string ToString() {
		if (this == nullptr) return "This entity has already been deleted. What are you doing?!";
		return "Entity " + name + " with GUID: " + std::to_string(guid);
	}

private:
	void AssignGUID(GUID guid) { this->guid = guid; }

public:
	std::string name;
	GUID guid = 0;

	Transform transform;
	SpriteRenderer renderer;
};