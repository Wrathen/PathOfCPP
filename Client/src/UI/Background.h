#pragma once
#include "../Components/SpriteRenderer.h"

class Background {
public:
	SpriteRenderer renderer;
	Transform transform;

	void SetProperties(std::string filePath, int w, int h) {
		transform.SetPosition(0, 0);
		renderer.AssignTransform(&transform);
		renderer.AssignTexture(filePath);
		renderer.SetWidth(w);
		renderer.SetHeight(h);
		//renderer.SetPositionAbsolute();
		renderer.shouldDrawCentered = true;
	}
	void Render() { renderer.Render(); }
};