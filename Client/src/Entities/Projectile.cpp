#include "Projectile.h"
#include "../Managers/CollisionManager.h"
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

	if (CheckIfTooFarAway()) {
		Delete();
		return;
	}
	CheckCollisions();

	Uint64 ticks = SDL_GetTicks64();
	if (ticks > lifetime) Delete();
}

bool Projectile::CheckIfTooFarAway() {
	auto screenPos = transform.GetScreenPosition();
	bool isFarAway = screenPos.x < -GAME.gameWidth/2 || screenPos.x > 3*GAME.gameWidth/2
				  || screenPos.y < -GAME.gameHeight/2 || screenPos.y > 3*GAME.gameHeight/2;
	return isFarAway;
}
void Projectile::CheckCollisions() {
	Vector2 myPos = transform.GetScreenPosition();
	Vector2 boxCollider(5, 5);
	Vector2 enemyBoxCollider(5, 5);
	int piercing = 2;

	auto allEntities = CollisionMgr.spatialHash.Query(myPos.x, myPos.y, 1, 1);
	//Debug(allEntities.size());
	for (auto* entity : allEntities) {
		if (entity->isToBeDeleted) continue;
		if (collisionTag == entity->collisionTag) continue;

		Vector2 pos = entity->transform.GetScreenPosition();
		bool hit = myPos.x + boxCollider.x > pos.x - enemyBoxCollider.x && myPos.x - boxCollider.x < pos.x + enemyBoxCollider.x &&
				   myPos.y + boxCollider.y > pos.y - enemyBoxCollider.y && myPos.y - boxCollider.y < pos.y + enemyBoxCollider.y;

		if (hit) {
			//Debug("[" + std::to_string(guid) + "] Colliding with: " + entity->ToString());
			source->OnKill();
			entity->Delete();

			if (--piercing <= 0) {
				Delete();
				break;
			}
		}
	}
}