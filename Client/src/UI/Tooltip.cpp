#include "Tooltip.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Random.h"

Tooltip::Tooltip() : UIElement("assets/sprites/Item/LootableItem.png") {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	Start();
}
void Tooltip::Start() {
	// Renderer background
	renderer.SetWidth(320);
	renderer.SetHeight(300);
	renderer.SetPositionAbsolute();

	// Name Text
	text_name.AssignTransform(&transform);
	text_name.SetWidth(300);
	text_name.SetHeight(40);
	text_name.SetFontSize(24);
	text_name.SetOffset(160, 26);
	text_name.SetPositionAbsolute();
	text_name.shouldDrawCentered = true;

	// Mods Text
	text_mods.AssignTransform(&transform);
	text_mods.SetWidth(300);
	text_mods.SetHeight(40);
	text_mods.SetFontSize(24);
	text_mods.SetOffset(15, 65);
	text_mods.SetPositionAbsolute();

	// Description Text
	text_description.AssignTransform(&transform);
	text_description.SetWidth(300);
	text_description.SetHeight(40);
	text_description.SetFontSize(18);
	text_description.SetOffset(10, 230);
	text_description.SetPositionAbsolute();
}
void Tooltip::Update() {
	if (!item) return;
	static float r = RandomInt(255);
	static float g = RandomInt(255);
	static float b = RandomInt(255);
	static bool rIncreasing = true;
	static bool gIncreasing = true;
	static bool bIncreasing = true;

	// Set color to White
	renderer.SetColor(255, 255, 255);

	// Rainbow effect for Artifact Rarity Items
	if (item->rarity == ItemRarity::Artifact) {
		r += rIncreasing ? 0.35f : -0.35f;
		g += gIncreasing ? 0.35f : -0.35f;
		b += bIncreasing ? 0.35f : -0.35f;
		rIncreasing = r > 254 ? false : r < 0.5f ? true : rIncreasing;
		gIncreasing = g > 254 ? false : g < 0.5f ? true : gIncreasing;
		bIncreasing = b > 254 ? false : b < 0.5f ? true : bIncreasing;

		renderer.SetColor((int)r, (int)g, (int)b);
	}

	// Set position of the tooltip to the Mouse Position
	transform.SetPosition(Mouse::GetPosition());

	// Clamp render area of the tooltip to be inside of the game screen.
	if (transform.position.x + renderer.width > GAME.gameWidth)
		transform.position.x -= transform.position.x + renderer.width - GAME.gameWidth;
	else if (transform.position.x < 0) transform.position.x = 0;

	if (transform.position.y + renderer.height > GAME.gameHeight)
		transform.position.y -= (transform.position.y + renderer.height) - GAME.gameHeight;
	else if (transform.position.y < 0) transform.position.y = 0;
}

void Tooltip::Render() {
	if (!item) return;

	renderer.Render();
	text_name.Render();
	text_mods.Render();
	text_description.Render();
}

void Tooltip::SetItem(Item* _item) { 
	if (item == _item) return;
	item = _item;
	if (!item) return;

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