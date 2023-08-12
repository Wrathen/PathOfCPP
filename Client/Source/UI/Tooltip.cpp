#include "Tooltip.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Random.h"

Tooltip::Tooltip() : UIElement("Assets/Sprites/Item/LootableItem.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	Start();
}
void Tooltip::Start() {
	SetInteractable(false);

	// Set the Z-Index to higher so it draws in front of everything else.
	zIndex = 100;

	// Renderer background
	renderer.SetWidth(460);
	renderer.SetHeight(400);
	renderer.SetPositionAbsolute();

	// Name Text
	text_name.AssignTransform(&transform);
	text_name.SetWidth(renderer.GetWidth() - 20);
	text_name.SetHeight(40);
	text_name.SetFontSize(24);
	text_name.SetOffset(renderer.GetWidth()/2, 34);
	text_name.SetPositionAbsolute();
	text_name.shouldDrawCentered = true;

	// Mods Text
	text_mods.AssignTransform(&transform);
	text_mods.SetWidth(380);
	text_mods.SetHeight(40);
	text_mods.SetFontSize(20);
	text_mods.SetOffset(15, 80);
	text_mods.SetPositionAbsolute();

	// Description Text
	text_description.AssignTransform(&transform);
	text_description.SetWidth(300);
	text_description.SetHeight(40);
	text_description.SetFontSize(18);
	text_description.SetOffset(10, renderer.GetHeight() - text_description.GetHeight());
	text_description.SetPositionAbsolute();
}
void Tooltip::Update() {
	if (!item) return;
	
	// Coloring
	{
		static float r = RandomInt(0, 255);
		static float g = RandomInt(0, 255);
		static float b = RandomInt(0, 255);
		static bool rIncreasing = true;
		static bool gIncreasing = true;
		static bool bIncreasing = true;

		// Rainbow effect for Artifact Rarity Items
		if (item->rarity == ItemRarity::Artifact) {
			r += (rIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
			g += (gIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
			b += (bIncreasing ? 255.0f : -255.0f) * Time::deltaTime;
			rIncreasing = r > 254 ? false : r < 0.5f ? true : rIncreasing;
			gIncreasing = g > 254 ? false : g < 0.5f ? true : gIncreasing;
			bIncreasing = b > 254 ? false : b < 0.5f ? true : bIncreasing;

			renderer.SetColor({(Uint8)r, (Uint8)g, (Uint8)b});
		} else renderer.SetColor({ 255, 255, 255 });
	}

	// Set position of the tooltip to the Mouse Position
	if (targetUIElement)
		transform.SetPosition(targetUIElement->transform.GetScreenPosition() - Vector2(renderer.GetWidth()/2, renderer.GetHeight()));

	// Clamp render area of the tooltip to be inside of the game screen.
	if (transform.position.x + renderer.width > GAME.screenWidth)
		transform.position.x -= transform.position.x + renderer.width - GAME.screenWidth;
	else if (transform.position.x < 0) transform.position.x = 0;

	if (transform.position.y + renderer.height > GAME.screenHeight)
		transform.position.y -= (transform.position.y + renderer.height) - GAME.screenHeight;
	else if (transform.position.y < 0) transform.position.y = 0;
}

void Tooltip::Render() {
	if (!item) return;

	renderer.Render();
	text_name.Render();
	text_mods.Render();
	text_description.Render();
}

void Tooltip::SetItem(UIElement* target, Item* _item) {
	// Update the Target UI Element
	targetUIElement = target;

	if (item == _item) return;
	item = _item;
	if (!_item) return;

	std::string name = item->GetName();
	if (name.size() > 23) text_name.SetFontSize(16);
	else text_name.SetFontSize(24);

	SDL_Color nameColor = item->rarity == ItemRarity::Common ? SDL_Color{255, 255, 255}:
		item->rarity == ItemRarity::Magic ? SDL_Color{ 94, 117, 235 } :
		item->rarity == ItemRarity::Rare ? SDL_Color{ 250, 237, 97 }:
		item->rarity == ItemRarity::Legendary ? SDL_Color{ 250, 115, 5 }:
		item->rarity == ItemRarity::Artifact ? SDL_Color{ 125, 240, 148 } : SDL_Color{ 255, 255, 255 };

	text_name.SetText(name, nameColor);
	text_mods.SetText(item->GetModsText(), { 85, 86, 174 });
	text_description.SetText(item->GetDescription(), { 77, 77, 77 });
}