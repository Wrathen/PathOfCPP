#include "BoxCollider.h"

void BoxCollider::SetProperties(int _w, int _h, int _xOffset, int _yOffset) {
	transform = &source->transform;
	w = _w;
	h = _h;
	xOffset = _xOffset;
	yOffset = _yOffset;
}

bool BoxCollider::Intersects(const BoxCollider& other) const {
	auto pos1 = transform->GetPosition();
	auto pos2 = other.transform->GetPosition();
	return pos1.x < pos2.x + other.w && pos1.x + w > pos2.x &&
		pos1.y < pos2.y + other.h && pos1.y + h > pos2.y;
}

void BoxCollider::OnCollisionEnter(Collider* other) {
	//Debug("Hey, I just collided with another collider!");
}