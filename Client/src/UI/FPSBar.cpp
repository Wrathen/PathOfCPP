#include "FPSBar.h"
#include "../Managers/GameManager.h"

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

void FPSBar::SetFPS(int FPS) { fpsText.SetText("FPS: " + std::to_string(FPS)); }