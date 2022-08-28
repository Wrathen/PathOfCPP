#include "HealthBar.h"

HealthBar::HealthBar(Entity* src): UIElement("assets/sprites/UI/healthbar/health.png") {
	targetEntity = src;
	targetTransform = &src->transform;
	targetStats = src->GetStats();

	bg_renderer.AssignTransform(&transform);
	bg_renderer.AssignTexture("assets/sprites/UI/healthbar/bg.png");
	Start();
}

void HealthBar::Start() {
	transform.SetScale(3.0f, 3.0f);
	renderer.SetPositionRelative();
	renderer.SetOffset(-25, -1); // Offset of frontground Health.png, (the Slider)
	offset = Vector2(0, -50.0f); // Transform Offset

	bg_renderer.shouldDrawCentered = true;
}
void HealthBar::Update() {
	transform.SetPosition(targetTransform->position + offset);
	if (!targetStats) return;

	int sliderMaxWidth = 15; // 15 is the MaxWidth we can achieve with the current configuration.
	int hpRatio = targetStats->health / targetStats->maxHealth * sliderMaxWidth;
	renderer.SetWidth(hpRatio);
}
void HealthBar::Render() {
	bg_renderer.Render();
	renderer.Render();
}