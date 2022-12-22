#include "UIElement.h"
#include "../Managers/UIManager.h"

UIElement::UIElement(std::string texturePath) {
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);

	UIMgr.Add(this);
	Start();
}

void UIElement::Start() { renderer.SetPositionAbsolute(); }
void UIElement::Update() {}
void UIElement::Render() { renderer.Render(); }
void UIElement::Delete() { UIMgr.Remove(this); }