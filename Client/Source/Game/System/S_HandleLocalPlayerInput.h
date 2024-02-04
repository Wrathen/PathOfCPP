#pragma once
#include "Core/Game/System/BaseSystem.h"

struct S_HandleLocalPlayerInput : Core::IBaseSystem {
	void HandleMovement();
	void HandleAbilities();

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Destroy() override;
};