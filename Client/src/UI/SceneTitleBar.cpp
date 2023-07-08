#include "SceneTitleBar.h"

SceneTitleBar::SceneTitleBar() : UIElement() {
	isAutomaticRenderingDisabled = true;
	Start();
}
void SceneTitleBar::Start() {
	// Title Text
	titleText.AssignTransform(&transform);
	titleText.SetWidth(1257);
	titleText.SetHeight(120);
	titleText.SetFontSize(64);
	titleText.SetPositionAbsolute();
	titleText.shouldDrawCentered = true;

	// Positioning
	transform.SetPosition(1920 / 2, 35);
}
void SceneTitleBar::Update() { }
void SceneTitleBar::Render() { titleText.Render(); }

void SceneTitleBar::SetTitle(std::string title) { titleText.SetText(title); }