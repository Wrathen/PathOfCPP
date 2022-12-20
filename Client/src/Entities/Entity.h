#pragma once
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Behaviour/StatBehaviour.h"
#include "../Components/SpriteRenderer.h"

// Temporary -- Delete Later
enum class EntityCollisionTag {
	Hostile,
	Friendly
};

class Entity: public StatBehaviour {
public:
	std::string name;
	GUID guid = 0;

	Transform transform;
	SpriteRenderer renderer;
	EntityCollisionTag collisionTag;

	bool isToBeDeleted = false;

public:
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
	virtual void OnKill() = 0;

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString();
};