#pragma once
#include "Scene.h"

class Scene_Town: public Scene {
public:
	Scene_Town();

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Clear() override;
};