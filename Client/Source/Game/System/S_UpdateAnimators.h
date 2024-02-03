#pragma once
#include "Core/Game/System/BaseSystem.h"

struct S_UpdateAnimators : Core::IBaseSystem {
	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Destroy() override;
};