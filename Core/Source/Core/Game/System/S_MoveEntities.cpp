#include "S_MoveEntities.h"
#include <iostream>
#include "Core/Managers/SceneManager.h"
#include "Core/Managers/CollisionManager.h"
#include "Core/Game/Component/Components.h"
#include <Core/Miscellaneous/Time.h>
#include <Core/Miscellaneous/Log.h>

void S_MoveEntities::Start() {

}

void S_MoveEntities::Update() {
	auto& reg = Core::SceneMgr.GetCurrentScene()->reg;
	auto group = reg.group<TransformComponent>(entt::get<StatsComponent>);

	group.each([&reg](auto entity, auto& transform, auto& stats) {
		Vector2 velocityNormalized = transform.velocity.Normalize();
		if (velocityNormalized.Magnitude() > 0.01f) {
			// Check if the target position is movable.
			Vector2 nextFramePosition = transform.position + (velocityNormalized * (stats.moveSpeed * Time::deltaTime));

			// If the entity has a BoxColliderComponent, we should also check whether the position is movable.
			if (reg.any_of<BoxColliderComponent>(entity)) {
				auto& collider = reg.get<BoxColliderComponent>(entity);
				Rect nextFrameRectX = Rect(nextFramePosition.x - collider.w / 2, transform.position.y - collider.h / 2,
					collider.w, collider.h);
				Rect nextFrameRectY = Rect(transform.position.x - collider.w / 2, nextFramePosition.y - collider.h / 2,
					collider.w, collider.h);

				if (!Core::CollisionMgr.IsPositionMovable(nextFrameRectX))
					transform.velocity.x = 0;
				if (!Core::CollisionMgr.IsPositionMovable(nextFrameRectY))
					transform.velocity.y = 0;

				nextFramePosition = transform.position + (transform.velocity.Normalize() * (stats.moveSpeed * Time::deltaTime));
			}

			// Set the new position.
			transform.position = nextFramePosition;
		}
	});
}

void S_MoveEntities::LateUpdate() {

}

void S_MoveEntities::Destroy() {
}