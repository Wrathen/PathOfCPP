#include "S_BaseMonsterAI.h"
#include <limits>
#include "Core/Managers/SceneManager.h"
#include "Core/Game/Component/Components.h"

static inline void LookForNearestEnemy(Core::BaseScene* scene, entt::entity entity, MonsterAIComponent& ai, TransformComponent& transform) {
	entt::entity closestPlayer = entt::null;
	float closestDistance = std::numeric_limits<float>::max();

	// In the future, we should be doing something better than this using spatialhash.
	// Find closest player
	for (size_t i = 0; i < scene->players.size(); ++i) {
		if (scene->players[i] == entt::null) continue;
		auto& playerTransform = scene->reg.get<TransformComponent>(scene->players[i]);
		float dist = playerTransform.position.DistanceToFast(transform.position);

		if (dist < ai.vicinityThreshold && dist < closestDistance) {
			closestPlayer = scene->players[i];
			closestDistance = dist;
		}
	}

	// If we couldn't find a player, return now.
	if (closestPlayer == entt::null)
		return;

	ai.target = closestPlayer;
	ai.state = MonsterAIState::Chasing;
}
static inline void ChaseTarget(Core::BaseScene* scene, entt::entity entity, MonsterAIComponent& ai, TransformComponent& transform) {
	if (ai.target == entt::null) {
		ai.state = MonsterAIState::Wandering;
		return;
	}

	// Check the distance to the target.
	auto& targetTransform = scene->reg.get<TransformComponent>(ai.target);
	float dist = targetTransform.position.DistanceToFast(transform.position);

	// If the target went too far, we should stop chasing after them.
	if (dist > ai.vicinityThreshold) {
		ai.target = entt::null;
		ai.state = MonsterAIState::Wandering;
		transform.velocity.x = 0;
		transform.velocity.y = 0;
		return;
	}

	// Chase the target.
	StatsComponent& stats = scene->reg.get<StatsComponent>(entity);
	float angle = Vector2::AngleBetween(transform.position, targetTransform.position);
	transform.velocity = Vector2::FromAngle(angle);
}
static inline void Evade(Core::BaseScene* scene, entt::entity entity, MonsterAIComponent& ai, TransformComponent& transform) {

}

void S_BaseMonsterAI::Update() {
	auto* scene = Core::SceneMgr.GetCurrentScene();
	auto& reg = scene->reg;
	auto group = reg.group<MonsterAIComponent>(entt::get<TransformComponent>);
	
	group.each([&](auto entity, MonsterAIComponent& ai, TransformComponent& transform) {
		switch (ai.state) {
			case MonsterAIState::Wandering:
				LookForNearestEnemy(scene, entity, ai, transform);
				break;
			case MonsterAIState::Chasing:
				ChaseTarget(scene, entity, ai, transform);
				break;
			case MonsterAIState::Evading:
				Evade(scene, entity, ai, transform);
				break;
		}
	});
}