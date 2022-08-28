#include "UIElement.h"
#include "../Managers/UIManager.h"

UIElement::UIElement(std::string texturePath) {
	UIMgr.AddElement(this);
	renderer.AssignTransform(&transform);
	renderer.AssignTexture(texturePath);

	Start();
}

void UIElement::Start() { renderer.SetPositionAbsolute(); }
void UIElement::Update() {}
void UIElement::Render() { renderer.Render(); }
void UIElement::Delete() { UIMgr.RemoveElement(this); }