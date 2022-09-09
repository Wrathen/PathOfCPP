#pragma once
#include "../../Entities/Entity.h"

typedef unsigned int uint;
class BoxCollider {
public:
	BoxCollider(Entity* _entity, uint width, uint height, uint offsetX, uint offsetY);
	bool Intersects(const BoxCollider& other) const;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int offsetX = 0;
	unsigned int offsetY = 0;

protected:
	Entity* entity;
	Transform* transform;
};