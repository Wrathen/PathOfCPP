#include "UIManager.h"
#include "GameManager.h"
#include "../Miscellaneous/Mouse.h"

void UIManager::Update() {
	Collection::Update();

	for (auto& element : *GetAll()) {
		//auto s = static_cast<HealthBar<Monster>*>(element.second);
		//s->UpdateDirect();
		//s->RenderDirect();
		element->Update();
		element->Render();
	}
}

bool UIManager::OnMouseDown() {
	Vector2 mousePos = Mouse::GetPosition();

	for (auto& element : *GetAll()) {
		if (!element->isInteractable) continue;
		auto target = element;

		Vector2 targetPos = target->transform.GetScreenPosition();
		auto targetWidth = target->renderer.width;
		auto targetHeight = target->renderer.height;

		bool collides = mousePos.x > targetPos.x && mousePos.x < targetPos.x + targetWidth &&
			mousePos.y > targetPos.y && mousePos.y < targetPos.y + targetHeight;
		
		if (collides) {
			bool raycastBlocked = target->OnClick();
			if (raycastBlocked) return true;
		}
	}

	return false;
}