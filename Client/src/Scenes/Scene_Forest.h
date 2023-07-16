#pragma once
#include "Scene.h"
#include "../UI/XPBar.h"
#include "../Miscellaneous/Timer.h"

class Scene_Forest : public Scene {
public:
	Scene_Forest();

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Clear() override;
};