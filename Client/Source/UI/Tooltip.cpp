#include "Tooltip.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Math.h"
#include "../Managers/InputManager.h"

Tooltip::Tooltip() : UIElement("Assets/Sprites/UI/Tooltip/Background.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	Start();
}
void Tooltip::Start() {
	SetInteractable(false);

	// Set the Z-Index to higher so it draws in front of everything else.
	zIndex = 100;

	// Title (sprite renderer)
	title.AssignTransform(&transform);
	title.AssignTexture("Assets/Sprites/UI/Tooltip/Title.png");
	title.SetWidth(460);

	// Renderer background
	renderer.SetWidth(460);
	renderer.SetHeight(400);
	renderer.SetPositionAbsolute();

	// Name Text
	text_name.AssignTransform(&transform);
	text_name.SetFontSize(24);
	text_name.SetOffset(renderer.GetWidth() / 2, 0);
	text_name.SetPositionAbsolute();
	text_name.shouldDrawCentered = true;

	// Mods Text
	text_mods.AssignTransform(&transform);
	text_mods.SetFontSize(20);
	text_mods.SetOffset(15, 80);
	text_mods.SetPositionAbsolute();
	text_mods.shouldDrawCentered = true;

	// Description Text
	text_description.AssignTransform(&transform);
	text_description.SetFontSize(18);
	text_description.SetOffset(10, renderer.GetHeight() - text_description.GetHeight());
	text_description.SetPositionAbsolute();
}
void Tooltip::Update() {
	if (!item) return;

	// Colorize this tooltip if it's an Artifact.
	if (item->rarity == ItemRarity::Artifact) ColorizeRainbow();
	else title.SetColor({ 255, 255, 255 });

	// Update the position of the tooltip.
	UpdatePosition();

	// #DEBUG [@TODO] DELETE
	if (InputMgr.IsKeyHeld(SDLK_5)) ChangeSize(600, 600);
}

void Tooltip::Render() {
	if (!item) return;

	renderer.Render();
	title.Render();
	text_name.Render();
	text_mods.Render();
	text_description.Render();
}

// Main Functions
void Tooltip::SetItem(UIElement* target, Item* _item, TooltipPositionType _positionType) {
	// Update the Target UI Element
	targetUIElement = target;
	// Update the PositionType.
	positionType = _positionType;

	// Do not to update if the item is the same as the cached one.
	// And also return if the parameter is nullptr.
	if (item == _item) return;
	item = _item;
	if (!_item) return;

	// Update the texts
	static SDL_Color nameColorings[5]{ {255, 255, 255}, {94, 117, 235}, {250, 237, 97}, {250, 115, 5}, {125, 240, 148} };
	text_name.SetText(item->GetName(), nameColorings[(int)item->rarity]);
	text_mods.SetText(item->GetModsText(), { 85, 86, 174 });
	text_description.SetText(item->GetDescription(), { 77, 77, 77 });

	// Dynamically calculate Width&Height of this tooltip box.
	uint32_t tooltipWidth = Max(text_name.GetWidth() + 30, text_mods.GetWidth(), text_description.GetWidth());
	uint32_t tooltipHeight = title.GetHeight() + text_name.GetHeight() + text_mods.GetHeight() + text_description.GetHeight();
	ChangeSize(tooltipWidth + 10, tooltipHeight + 10);
}

void Tooltip::UpdatePosition() {
	if (positionType == TooltipPositionType::NONE)
		return;

	// Update Position
	{
		// Set position of the tooltip to the Mouse Position
		if (targetUIElement) {
			// By default, it's TooltipPositionType::InventoryItem
			Vector2 newPosition = (targetUIElement->transform.GetScreenPosition() -
								   Vector2(renderer.GetWidth() / 2, renderer.GetHeight()));

			// If the positionType is LootableItem, then we should draw it on the most-right just above mana bar.
			if (positionType == TooltipPositionType::LootableItem) {
				// [@todo] hardcoded 830, should be a variable that represent just the top of ManaBar.
				// screenHeight - ManaBarHeight() - smallOffset
				newPosition = Vector2(GAME.screenWidth - renderer.GetWidth(), 830 - renderer.GetHeight());
			}
			//else if (positionType == TooltipPositionType::EquipmentItem)

			// And finally, set the new position.
			transform.SetPosition(newPosition);
		}
	}

	// Clamp
	{
		// Clamp render area of the tooltip to be inside of the game screen.
		auto pos = transform.GetPosition();
		if (pos.x + renderer.width > GAME.screenWidth)
			pos.x -= transform.GetPosition().x + renderer.width - GAME.screenWidth;
		else if (pos.x < 0) pos.x = 0;

		if (pos.y + renderer.height > GAME.screenHeight)
			pos.y -= (pos.y + renderer.height) - GAME.screenHeight;
		else if (pos.y < 0) pos.y = 0;

		transform.SetPosition(pos);
	}
}
// Rainbow effect for Artifact Rarity Items
void Tooltip::ColorizeRainbow() {
	static float r = RandomInt(0, 255);
	static float g = RandomInt(0, 255);
	static float b = RandomInt(0, 255);
	static bool rIncreasing = true;
	static bool gIncreasing = true;
	static bool bIncreasing = true;

	r += (rIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
	g += (gIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
	b += (bIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
	rIncreasing = r > 254 ? false : r < 0.5f ? true : rIncreasing;
	gIncreasing = g > 254 ? false : g < 0.5f ? true : gIncreasing;
	bIncreasing = b > 254 ? false : b < 0.5f ? true : bIncreasing;

	title.SetColor({ (Uint8)r, (Uint8)g, (Uint8)b });
}

void Tooltip::ChangeSize(uint32_t newWidth, uint32_t newHeight) {
	renderer.SetWidth(newWidth);
	renderer.SetHeight(newHeight);

	title.SetWidth(newWidth);

	text_name.SetOffset(newWidth / 2, title.GetHeight() / 2);
	text_mods.SetOffset(newWidth / 2, title.GetHeight() + text_mods.GetHeight() / 2 + 10);
	text_description.SetOffset(10, renderer.GetHeight() - text_description.GetHeight());
}