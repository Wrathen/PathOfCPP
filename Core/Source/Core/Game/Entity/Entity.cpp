#include "Entity.h"
#include "Core/Miscellaneous/ErrorHandler.h"

namespace Core {
	Entity::Entity(BaseScene* _scene, entt::entity enttEntity) {
		if (enttEntity == entt::null) {
			Abort("An Entity object was trying to be created with an entt::null parameter", "Fatal error!");
			return;
		}
		if (!_scene) {
			Abort("An invalid scene parameter was given while creating an Entity from an existing Entt::Entity.", "Fatal error!");
			return;
		}

		raw_entity = enttEntity;
		scene = _scene;
	}

	Entity::Entity(BaseScene* _scene) : scene(_scene) {
		if (!scene) {
			Abort("An invalid scene parameter was given while creating an Entity.", "Fatal error!");
			return;
		}

		raw_entity = scene->reg.create();
	}
}