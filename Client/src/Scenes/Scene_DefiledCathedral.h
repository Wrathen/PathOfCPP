#pragma once
#include "Scene.h"

class Scene_DefiledCathedral: public Scene {
public:
	Scene_DefiledCathedral();

	void Start() override;
	void Update() override;
	void LateUpdate() override;
	void Clear() override;
};

