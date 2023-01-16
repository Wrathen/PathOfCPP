#include "UIElement.h"
#include "../Managers/UIManager.h"

UIElement::UIElement(std::string texturePath) {
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);

	UIMgr.Add(this);
	renderer.SetPositionAbsolute();
}

void UIElement::Start() {}
void UIElement::Update() {}
void UIElement::Render() { renderer.Render(); }
void UIElement::Delete() { UIMgr.Remove(this); }

bool UIElement::OnClick() { return isBlockingRaycasts; }