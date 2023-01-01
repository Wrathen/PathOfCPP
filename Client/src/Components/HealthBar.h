#pragma once
#include "../UI/UIElement.h"
#include "../Entities/Entity.h"
#include "Stats.h"
#include "Component.h"

class HealthBar: public Component, public UIElement {
public:
	Transform* sourceTransform = nullptr;
	Stats* stats = nullptr;

	SpriteRenderer bg_renderer;
	Vector2 offset;

	HealthBar() : UIElement("assets/sprites/UI/healthbar/health.png") {}
	void Start() override {
		sourceTransform = &source->transform;

		bg_renderer.AssignTransform(&transform);
		bg_renderer.AssignTexture("assets/sprites/UI/healthbar/bg.png");

		transform.SetScale(3.0f, 3.0f);
		renderer.SetPositionRelative();
		renderer.SetOffset(-25, -1); // Offset of frontground Health.png, (the Slider)
		offset = Vector2(0, -50.0f); // Transform Offset

		bg_renderer.shouldDrawCentered = true;
		stats = source->GetComponent<Stats>();
	}
	void Update() override {
		if (!source || !stats) return;

		int sliderMaxWidth = 15; // 15 is the MaxWidth we can achieve with the current configuration.
		int hpRatio = stats->GetHealth() / stats->GetMaxHealth() * sliderMaxWidth;
		renderer.SetWidth(hpRatio);

		transform.SetPosition(sourceTransform->position + offset);
	}
	void Render() override {
		bg_renderer.Render();
		renderer.Render();
	}
};