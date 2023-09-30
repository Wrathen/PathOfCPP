#include "HealthBar.h"

HealthBar::HealthBar() : UIElement("Assets/Sprites/UI/HealthBar/health.png") {}
void HealthBar::Start() {
	SetInteractable(false);
	sourceTransform = &source->transform;

	bg_renderer.AssignTransform(&transform);
	bg_renderer.AssignTexture("Assets/Sprites/UI/HealthBar/bg.png");

	transform.SetScale(3.0f, 3.0f);
	renderer.SetPositionRelative();
	renderer.SetOffset(-25, -1); // Offset of frontground Health.png, (the Slider)
	offset = Vector2(0, -50.0f); // Transform Offset

	bg_renderer.shouldDrawCentered = true;
	healthComponent = source->GetComponent<Health>();
}
void HealthBar::Update() {
	if (!source || !healthComponent) return;

	int sliderMaxWidth = 15; // 15 is the MaxWidth we can achieve with the current configuration.
	float hpRatio = healthComponent->GetHealth() / healthComponent->GetMaxHealth() * sliderMaxWidth;
	renderer.SetWidth(hpRatio);

	transform.SetPosition(sourceTransform->GetPosition() + offset);
}
void HealthBar::Render() {
	bg_renderer.Render();
	renderer.Render();
}