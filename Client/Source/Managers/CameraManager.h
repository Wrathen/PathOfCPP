#pragma once
#include "Core/Miscellaneous/Vector.h"

#define Camera CameraManager::GetInstance()
class CameraManager {
public:
	static CameraManager& GetInstance() { static CameraManager _i; return _i; }

	// Base Functions
	void Update();

	// Main Functions
	const Vector2& GetPosition() const { return position; }

	Vector2 position = Vector2(0, 0);

private:
	CameraManager() {}
	~CameraManager() {}
	CameraManager(CameraManager const&) = delete;
	void operator=(CameraManager const&) = delete;
};