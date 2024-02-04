#include "S_MoveEntities.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Managers/CollisionManager.h"
#include "Core/Game/Component/Components.h"
#include <Core/Miscellaneous/Time.h>
#include <Core/Miscellaneous/Log.h>

void S_MoveEntities::Update() {
	auto& reg = Core::SceneMgr.GetCurrentScene()->reg;
	auto group = reg.group<TransformComponent>(entt::get<StatsComponent>);

	group.each([&reg](auto entity, auto& transform, auto& stats) {
		Vector2 velocityNormalized = transform.velocity.Normalize();
		if (velocityNormalized.Magnitude() > 0.01f) {
			// Check if the target position is movable.
			Vector2 nextFramePosition = transform.position + (velocityNormalized * (stats.moveSpeed * (float)Time::deltaTime));

			// If the entity has a BoxColliderComponent, we should also check whether the position is movable.
			if (reg.any_of<BoxColliderComponent>(entity)) {
				auto& collider = reg.get<BoxColliderComponent>(entity);
				Rect newPosHorizontal = Rect((int)(nextFramePosition.x - collider.w / 2), 
										     (int)(transform.position.y - collider.h / 2),
										     collider.w, collider.h);
				Rect newPosVertical   = Rect((int)(transform.position.x - collider.w / 2),
									     	 (int)(nextFramePosition.y - collider.h / 2),
										     collider.w, collider.h);

				// Check whether the next frame position is occupied.
				CollisionResult resultHorizontal = Core::CollisionMgr.IsPositionOccupied(newPosHorizontal);
				CollisionResult resultVertical = Core::CollisionMgr.IsPositionOccupied(newPosVertical);
				
				// If any collision happened either Horizontal or Vertical, we need to update the nextFramePosition accordingly.
				if (resultHorizontal || resultVertical) {
					if (resultHorizontal) transform.velocity.x = 0;
					if (resultVertical) transform.velocity.y = 0;

					nextFramePosition = transform.position + (transform.velocity.Normalize() * (stats.moveSpeed * (float)Time::deltaTime));
				}
			}

			// Set the new position.
			transform.position = nextFramePosition;
		}
	});
}