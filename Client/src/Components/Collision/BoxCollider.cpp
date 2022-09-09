#include "BoxCollider.h"

BoxCollider::BoxCollider(Entity* _entity, uint width = 0, uint height = 0, uint offsetX = 0, uint offsetY = 0){
	entity = _entity;
	transform = &entity->transform;
}

bool BoxCollider::Intersects(const BoxCollider& other) const {
	Vector2 pos = transform->GetPosition();
	// continue from here... Vector2 other = (&(other.transform))->GetPosition();
	return false;
}