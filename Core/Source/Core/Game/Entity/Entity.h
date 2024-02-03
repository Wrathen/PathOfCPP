#pragma once
#include <entt.hpp>
#include "Core/Game/Scene/Scene.h"

namespace Core {
	// This class is can be used as a temporary object as all it does is just provide some Utility.
	// It is only 16 bytes.

	struct Entity {
		Entity() = default;
		Entity(BaseScene* _scene, entt::entity enttEntity);
		Entity(BaseScene* _scene);
		Entity(const Entity&) = default;

		template <typename T, typename... Args>
		T& AddComponent(Args... args) {
			return scene->reg.emplace<T>(raw_entity, std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent() {
			scene->reg.remove<T>(raw_entity);
		}

		template <typename T>
		bool HasComponent() {
			return scene->reg.any_of<T>(raw_entity);
		}

		template <typename T>
		T& GetComponent() {
			return scene->reg.get<T>(raw_entity);
		}

		operator bool() {
			return scene && scene->isActive && raw_entity != entt::null;
		}

	private:
		entt::entity raw_entity = entt::null;
		BaseScene* scene = nullptr;
	
	public:
		entt::entity GetRaw() { return raw_entity; }
		BaseScene* GetScene() { return scene; }
	};
}