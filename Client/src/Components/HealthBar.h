#pragma once
#include "../UI/UIElement.h"
#include "../Entities/Entity.h"

template <typename T>
class HealthBar: public UIElement {
public:
	HealthBar<T>(T* src) : UIElement("assets/sprites/UI/healthbar/health.png") {
		sourceEntity = src;
		sourceTransform = &src->transform;

		bg_renderer.AssignTransform(&transform);
		bg_renderer.AssignTexture("assets/sprites/UI/healthbar/bg.png");
		Start();
	}
	void Start() override {
		transform.SetScale(3.0f, 3.0f);
		renderer.SetPositionRelative();
		renderer.SetOffset(-25, -1); // Offset of frontground Health.png, (the Slider)
		offset = Vector2(0, -50.0f); // Transform Offset

		bg_renderer.shouldDrawCentered = true;
	}
	void Update() override {
		transform.SetPosition(sourceTransform->position + offset);
		if (!sourceEntity) return;

		int sliderMaxWidth = 15; // 15 is the MaxWidth we can achieve with the current configuration.
		int hpRatio = sourceEntity->GetHealth() / sourceEntity->GetMaxHealth() * sliderMaxWidth;
		renderer.SetWidth(hpRatio);
	}
	void Render() override {
		bg_renderer.Render();
		renderer.Render();
	}

	T* sourceEntity;
	Transform* sourceTransform;

	SpriteRenderer bg_renderer;
	Vector2 offset;
};