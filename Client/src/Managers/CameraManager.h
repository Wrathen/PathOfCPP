#pragma once
#include "../Entities/Entity.h"

#define Camera CameraManager::GetInstance()
class CameraManager {
public:
	static CameraManager& GetInstance() {
		static CameraManager instance;
		return instance;
	}

	// Base Functions
	void Update();

	// Main Functions
	void SetTarget(Entity* t) { target = t; }
	const Vector2& GetPosition() { return transform.position; }

	Entity* target;
	Transform transform;
};