#pragma once
#include <string>
#include "../Component.h"
#include "../../Entities/Entity.h"
#include "../../Miscellaneous/GUID.h"

class Collider: public Component {
public:
	Transform* transform;
	GUID guid = 0;
	bool isToBeDeleted = false;

	// Base Functions
	virtual ~Collider() = default;

	virtual void Start();
	virtual void Update();

	// Main Functions
	void Delete();
	virtual void OnCollisionEnter(Collider* other) = 0;

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString();
};