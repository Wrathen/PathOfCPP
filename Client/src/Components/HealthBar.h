#pragma once
#include "../UI/UIElement.h"
#include "../Entities/Entity.h"

class HealthBar: public UIElement {
public:
	HealthBar(Entity* src);
	void Start() override;
	void Update() override;
	void Render() override;

	Entity* targetEntity;
	Transform* targetTransform;
	const Stats* targetStats;

	SpriteRenderer bg_renderer;
	Vector2 offset;
};