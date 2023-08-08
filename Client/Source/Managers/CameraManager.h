#pragma once
#include "../Miscellaneous/Singleton.h"
#include "../Entities/Entity.h"

#define Camera CameraManager::GetInstance()
class CameraManager : public Singleton<CameraManager> { friend class Singleton;
public:
	Entity* target = nullptr;
	Transform transform;

	// Base Functions
	void Update();

	// Main Functions
	void SetTarget(Entity* t) { target = t; }
	const Vector2& GetPosition() const { return transform.position; }

private:
	CameraManager() {}
	~CameraManager() {}
	CameraManager(CameraManager const&) = delete;
	void operator=(CameraManager const&) = delete;
};