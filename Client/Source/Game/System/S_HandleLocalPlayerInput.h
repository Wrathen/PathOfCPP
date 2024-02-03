#pragma once
#include "Core/Game/System/BaseSystem.h"
#include "Core/Game/Entity/Entity.h"

struct S_HandleLocalPlayerInput : Core::IBaseSystem {
	void HandleMovement();
	void HandleAbilities();
	void HandleDebug();

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Destroy() override;
};