#include "Projectile.h"
#include "../Managers/EntityManager.h"
#include "../Miscellaneous/Log.h"

Projectile::Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration) : Entity("assets/sprites/arrow.png", "Arrow") {
	collisionTag = EntityCollisionTag::Friendly;
	source = src;

	Vector2 velocity = Vector2::FromAngle(rotation) * speed;
	transform.SetVelocity(velocity);
	transform.SetPosition(position);
	transform.SetRotation(rotation);

	lifetime = SDL_GetTicks64() + static_cast<int>(duration * 1000);
	Start();
}

void Projectile::Start() { }
void Projectile::Update() {
	transform.Move();
	CheckCollisions();

	Uint64 ticks = SDL_GetTicks64();
	if (ticks > lifetime) Delete();
}

// THIS IS DEBUG-ONLY. WILL IMPLEMENT MUCH BETTER COLLISION DETECTION soon(tm).
// Just trying to have some fun while coding. This made my day for now.
// Even though this is terrible bruteforce collision detection, I'm actually surprised by how C++
// is performing. It's insane. I'm loving this language already. Give me more! :D
void Projectile::CheckCollisions() {
	auto allEntities = EntityMgr.GetAll();
	Vector2 myPos = transform.GetPosition();
	Vector2 boxCollider(5, 5);
	Vector2 enemyBoxCollider(5, 5);

	bool piercing = true;
	for (auto& entity : *allEntities) {
		if (entity.second->isToBeDeleted) continue;
		if (collisionTag == entity.second->collisionTag) continue;

		Vector2 pos = entity.second->transform.GetPosition();
		bool hit = myPos.x + boxCollider.x > pos.x - enemyBoxCollider.x && myPos.x - boxCollider.x < pos.x + enemyBoxCollider.x &&
				   myPos.y + boxCollider.y > pos.y - enemyBoxCollider.y && myPos.y - boxCollider.y < pos.y + enemyBoxCollider.y;

		if (hit) {
			//Debug("[" + std::to_string(guid) + "] Colliding with: " + entity.second->ToString());
			source->OnKill();
			entity.second->Delete();

			if (!piercing) {
				Delete();
				break;
			}
		}
	}
}