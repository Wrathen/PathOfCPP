#include "PowerUpGroup.h"
#include "../Managers/GameManager.h"

PowerUpGroup::PowerUpGroup() : UIElement() {
	SetVisible(false);
	SetInteractable(false);
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
}

void PowerUpGroup::GeneratePowerUps() {
	power1 = PowerUp::GetRandom();
	while (power2 == nullptr || power1 == power2)
		power2 = PowerUp::GetRandom();
	while (power3 == nullptr || power1 == power3 || power2 == power3)
		power3 = PowerUp::GetRandom();

	int w = PowerUp::width;
	int h = PowerUp::height;
	int screenCenterX = GAME.screenWidth / 2;
	int screenCenterY = GAME.screenHeight / 2;

	power1->transform.SetPosition(screenCenterX - w, screenCenterY);
	power2->transform.SetPosition(screenCenterX, screenCenterY);
	power3->transform.SetPosition(screenCenterX + w, screenCenterY);
}

std::vector<UIElement*> PowerUpGroup::GetCurrentShownPowerUps() {
	return std::vector<UIElement*>{ power1, power2, power3 };
}

void PowerUpGroup::Clear() {
	power1->transform.SetPosition(-1000, -1000);
	power2->transform.SetPosition(-1000, -1000);
	power3->transform.SetPosition(-1000, -1000);

	power1 = nullptr;
	power2 = nullptr;
	power3 = nullptr;
}

void PowerUpGroup::Render() {
	if (power1) power1->Render();
	if (power2) power2->Render();
	if (power3) power3->Render();
}
