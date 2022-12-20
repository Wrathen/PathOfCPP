#pragma once
#include "Collider.h"
#include "../../Entities/Entity.h"

class BoxCollider: public Collider {
public:
	BoxCollider(Entity* _entity, uint width, uint height, uint offsetX, uint offsetY);
	bool Intersects(const BoxCollider& other) const;

	uint width = 0;
	uint height = 0;
	uint offsetX = 0;
	uint offsetY = 0;

	virtual void OnCollisionEnter(Entity* col) = 0;
protected:
	Entity* entity;
	Transform* transform;
};