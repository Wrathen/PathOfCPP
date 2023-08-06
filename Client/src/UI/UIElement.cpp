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
void UIElement::Delete() { OnDelete(); UIMgr.Remove(this); }

bool UIElement::OnClick() { return isBlockingRaycasts; }
bool UIElement::OnApplyItem(UIItem* item) { return canItemsBeApplied; }

void UIElement::SetVisible(bool value) { renderer.SetVisible(value); }
bool UIElement::GetVisible() { return renderer.GetVisible(); }
void UIElement::SetInteractable(bool value) { isInteractable = value; }

void UIElement::AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
std::string UIElement::ToString() {
	if (!this) return "This UIElement has already been deleted. What are you doing?!";
	return "UIElement with GUID: " + std::to_string(guid);
}