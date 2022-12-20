#pragma once
#include <string>
#include "../../Miscellaneous/GUID.h"

typedef unsigned int uint;

class Collider
{
public:
	GUID guid = 0;
	bool isToBeDeleted = false;

	// Base Functions
	Collider();
	virtual ~Collider() = default;

	virtual void Start() = 0;
	virtual void Update() = 0;

	// Main Functions
	void Delete();

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString();
};