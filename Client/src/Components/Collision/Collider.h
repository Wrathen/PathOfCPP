#pragma once
#include <string>
#include "../../Entities/Entity.h"
#include "../../Miscellaneous/GUID.h"

class Collider {
public:
	Entity* entity;
	Transform* transform;
	GUID guid = 0;
	bool isToBeDeleted = false;

	// Base Functions
	Collider();
	virtual ~Collider() = default;

	virtual void Start() = 0;
	virtual void Update() = 0;

	// Main Functions
	void Delete();
	virtual void OnCollisionEnter(Collider* other) = 0;

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString();
};