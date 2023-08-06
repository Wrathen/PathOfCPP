#include "FPSBar.h"
#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"
#include "../Miscellaneous/Mouse.h"

FPSBar::FPSBar() : UIElement() {
	isAutomaticRenderingDisabled = true;
	isToBeDeletedOnSceneChange = false;
	Start();
}

void FPSBar::Start() {
	// FPS Text
	fpsText.AssignTransform(&transform);
	fpsText.SetWidth(1257);
	fpsText.SetHeight(120);
	fpsText.SetFontSize(48);
	fpsText.SetPositionAbsolute();

	// Positioning
	transform.SetPosition(15, 15);

	renderer.SetPositionAbsolute();
}
void FPSBar::Update() {}
void FPSBar::Render() { fpsText.Render(); }

void FPSBar::SetFPS(int FPS) {
	if (InputMgr.IsKeyHeld(SDLK_4)) {
		auto mousePos = Mouse::GetPosition();
		fpsText.SetText("MousePosition: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
	}
	else
		fpsText.SetText("FPS: " + std::to_string(FPS));
}