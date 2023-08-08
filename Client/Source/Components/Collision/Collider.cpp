#include "Collider.h"
#include "../../Managers/CollisionManager.h"

void Collider::Start() { CollisionMgr.Add(this); }
void Collider::Update() {}
void Collider::Delete() { CollisionMgr.Remove(this); }

std::string Collider::ToString() {
	if (!this) return "This collider has already been deleted. What are you doing?!";
	return "BaseClass Collider with GUID: " + std::to_string(guid);
}