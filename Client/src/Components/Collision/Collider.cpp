#include "Collider.h"
#include "../../Managers/CollisionManager.h"

Collider::Collider() { CollisionMgr.Add(this); }
void Collider::Delete() { CollisionMgr.Remove(this); }

std::string Collider::ToString() {
	if (!this) return "This collider has already been deleted. What are you doing?!";
	return "BaseClass Collider with GUID: " + std::to_string(guid);
}