#include "XPBar.h"
#include "../Miscellaneous/Log.h"

// [TO-DO] FIX HARD CODED STUFF
// THERE IS A LOT OF HARD CODING IN HERE

XPBar::XPBar() : UIElement("assets/sprites/UI/xpbar/frontground.png") { Start(); }
void XPBar::Start() {
	corners_renderer.AssignTransform(&transform);
	corners_renderer.AssignTexture("assets/sprites/UI/xpbar/corners.png");

	background_renderer.AssignTransform(&transform);
	background_renderer.AssignTexture("assets/sprites/UI/xpbar/background.png");

	// Level Text
	levelText.AssignTransform(&transform);
	levelText.SetWidth(1257);
	levelText.SetHeight(120);
	levelText.SetOffset(0, -45);
	levelText.SetFontSize(64);
	levelText.SetPositionAbsolute();
	
	levelText.shouldDrawCentered = true;

	// Positioning
	transform.SetPosition(1920/2, 1080-renderer.height/2);
	transform.SetScale(0.5f, 0.35f);

	renderer.SetPositionAbsolute();
	corners_renderer.SetPositionAbsolute();
	background_renderer.SetPositionAbsolute();

	corners_renderer.shouldDrawCentered = true;
	background_renderer.shouldDrawCentered = true;

	renderer.SetOffset(-1260/2 * 0.5f, -128/2 * 0.35f - 2);
	background_renderer.SetOffset(0, -2);

}
void XPBar::Update() {
	int sliderMaxWidth = 1260;
	float xpRatio = xp / maxXP * sliderMaxWidth;
	renderer.SetWidth(xpRatio);
}
void XPBar::Render() {
	background_renderer.Render();
	renderer.Render();
	corners_renderer.Render();
	levelText.Render();
}

void XPBar::SetXP(float _xp) { xp = _xp; }
void XPBar::SetMaxXP(float _maxXP) { maxXP = _maxXP; }
void XPBar::SetLevel(int _level) {
	level = _level;
	levelText.SetText("Level " + std::to_string(level), { 0, 0, 0 });
}