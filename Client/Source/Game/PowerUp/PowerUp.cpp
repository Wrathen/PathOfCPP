#include "PowerUp.h"
#include "AllPowerUps.cpp"
#include "../../UI/UserInterface.h"
#include "../../Managers/GameManager.h"
#include "../../Miscellaneous/Log.h"
#include "../../Miscellaneous/Random.h"

PowerUp::PowerUp(std::string _text, std::string _description, FuncOnPowerUp funcOnPowerUp): 
	text(_text), description(_description), OnPowerUp(funcOnPowerUp),
	UIElement("Assets/Sprites/UI/PowerUp/background.png")
{
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	isBlockingRaycasts = true;
	isInteractable = true;
	Start();
}

void PowerUp::Start() {
	// Set Position off the screen
	transform.SetPosition(-1000, -1000);

	// Set Renderer Properties
	renderer.SetWidth(width);
	renderer.SetHeight(height);
	renderer.SetPositionAbsolute();
	renderer.shouldDrawCentered = true;

	// Set Text_Name Properties
	auto charCount = text.size();
	text_name.AssignTransform(&transform);
	text_name.SetWidth(width - 200);
	text_name.SetHeight(60);
	text_name.SetOffset(0, -height/3 + 50);
	text_name.SetPositionAbsolute();
	text_name.SetText(text, { 255, 51, 5 });
	text_name.SetFontSize(charCount < 12 ? 32 : charCount < 16 ? 28 : charCount < 18 ? 26 : 20);
	text_name.shouldDrawCentered = true;

	// Set Text_Description Properties
	text_description.AssignTransform(&transform);
	text_description.SetWidth(width - 50);
	text_description.SetHeight(60);
	text_description.SetOffset(-width / 3, -height / 3 + 120);
	text_description.SetPositionAbsolute();
	text_description.SetText(description, { 255, 255, 255 });
	text_description.SetFontSize(18);
}
void PowerUp::Render() {
	// DEBUG
	auto namePos = text_name.transform->GetScreenPosition();
	auto descPos = text_description.transform->GetScreenPosition();
	GAME.DrawRect(namePos + text_name.GetOffset() - Vector2(text_name.width / 2, text_name.height / 2), text_name.width, text_name.height);
	GAME.DrawRect(descPos + text_description.GetOffset(), text_description.width, text_description.height);

	renderer.Render();
	text_name.Render();
	text_description.Render();
}

bool PowerUp::OnClick() {
	if (OnPowerUp) OnPowerUp();

	// Handle UI
	UI.ClearPowerUps();
	UI.HidePowerUps();
	UI.ShowTooltip();

	GAME.PauseGame(false);

	// Add stuff to the Player Stats
	return isBlockingRaycasts;
}

// Static Function
PowerUp* PowerUp::GetRandom() {
	constexpr auto size = std::size(allPowerUps);
	return allPowerUps[RandomInt(0, size)];
}