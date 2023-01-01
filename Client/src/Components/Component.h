#pragma once
#include "../Entities/Entity.h"
#include "../Miscellaneous/Log.h"

class Component {
public:
	Entity* source = nullptr;

	void SetSource(Entity* entity) { source = entity; }

	virtual void Start() = 0;
};