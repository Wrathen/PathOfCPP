#pragma once
#include "Scene.h"
#include "../UI/XPBar.h"

class Scene_Forest : public Scene {
public:
	XPBar* xpBar = nullptr;

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Clear() override;
};