#include "CurrencyBar.h"
#include "../Managers/GameManager.h"

CurrencyBar::CurrencyBar() : UIElement("Assets/Sprites/UI/CurrencyBar/currency.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	Start();
}

void CurrencyBar::Start() {
	// Gold Text
	goldText.AssignTransform(&transform);
	goldText.SetWidth(1257);
	goldText.SetHeight(120);
	goldText.SetFontSize(48);
	goldText.SetPositionAbsolute();
	goldText.SetOffset(renderer.width + 15, 0);

	// Positioning
	transform.SetPosition(15, GAME.screenHeight - renderer.height - 15);

	renderer.SetPositionAbsolute();
}
void CurrencyBar::Update() {}
void CurrencyBar::Render() {
	renderer.Render();
	goldText.Render();
}

void CurrencyBar::SetGold(int _gold) {
	if (gold == _gold) return;
	gold = _gold;

	goldText.SetText(std::to_string(gold) + " Gold", { 0, 0, 0 });
}