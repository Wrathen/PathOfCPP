#include "Projectile.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Timer.h"
#include "../Components/Collision/BoxCollider.h"
#include "../Components/Stats.h"

Projectile::Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration) : Entity("assets/sprites/arrow.png", "Arrow") {
	source = src;

	// Transform
	Vector2 velocity = Vector2::FromAngle(rotation) * speed;
	transform.SetVelocity(velocity);
	transform.SetPosition(position);
	transform.SetRotation(rotation);

	lifetime = SDL_GetTicks64() + static_cast<int>(duration * 1000);
	collisionTag = EntityCollisionTag::Friendly;

	Start();
}

void Projectile::Start() {
	Stats* stats = source->GetComponent<Stats>();
	if (!stats) {
		Warn("Projectile object somehow didn't retrieve a suitable Stats source!");
		return;
	}

	piercingAmount = stats->GetPiercingAmount();
	damageAmount = stats->GetDamageAmount();
}
void Projectile::Update() {
	transform.Move();

	if (CheckIfTooFarAway()) {
		Delete();
		return;
	}
	CheckCollisions();
	CheckLifetime();
}

bool Projectile::CheckIfTooFarAway() {
	auto screenPos = transform.GetScreenPosition();
	bool isFarAway = screenPos.x < -GAME.gameWidth/2 || screenPos.x > 3*GAME.gameWidth/2
				  || screenPos.y < -GAME.gameHeight/2 || screenPos.y > 3*GAME.gameHeight/2;
	return isFarAway;
}
void Projectile::CheckLifetime() {
	Uint64 ticks = SDL_GetTicks64();
	if (ticks > lifetime) Delete();
}
void Projectile::CheckCollisions() {
	Vector2 myPos = transform.GetScreenPosition() - boxCollider / 2;
	
	// [Debug -- DELETE LATER] draw collisions
	//GAME.DrawRect(myPos, boxCollider.x, boxCollider.y);
	auto& allEntities = CollisionMgr.spatialHash.Query(myPos.x, myPos.y, 2, 2);

	for (auto& entity : allEntities) {
		if (entity->isToBeDeleted) {
			CollisionMgr.spatialHash.Remove(entity);
			continue;
		}

		// [Debug -- DELETE LATER] draw collisions
		//GAME.DrawRect(entity->transform.GetScreenPosition() - enemyBoxCollider / 2, enemyBoxCollider.x, enemyBoxCollider.y);

		Vector2 pos = entity->transform.GetScreenPosition();
		bool hit = myPos.x > pos.x - enemyBoxCollider.x/2 && myPos.x < pos.x + enemyBoxCollider.x/2 &&
				   myPos.y > pos.y - enemyBoxCollider.y/2 && myPos.y < pos.y + enemyBoxCollider.y/2;

		if (hit) {
			//Debug("[" + std::to_string(guid) + "] Colliding with: " + entity->ToString());
			source->OnKill();
			entity->OnDeath();
			entity->Delete();

			if (--piercingAmount <= 0) {
				Delete();
				break;
			}
		}
	}
}