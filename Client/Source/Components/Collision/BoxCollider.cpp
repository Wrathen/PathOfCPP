#include "BoxCollider.h"

// Setters and Getters
void BoxCollider::SetWidth(int _w) { w = _w; }
void BoxCollider::SetHeight(int _h) { h = _h; }
Rect BoxCollider::GetBoundaries() {
	auto& position = (&source->transform)->GetPosition();
	return Rect(position.x - w, position.y - h, w, h);
}

bool BoxCollider::Intersects(const BoxCollider& other) const {
	auto& pos1 = transform->GetPosition();
	auto& pos2 = other.transform->GetPosition();
	return pos1.x < pos2.x + other.w && pos1.x + w > pos2.x &&
		pos1.y < pos2.y + other.h && pos1.y + h > pos2.y;
}

void BoxCollider::OnCollisionEnter(Collider* other) {
	//Debug("Hey, I just collided with another collider!");
}