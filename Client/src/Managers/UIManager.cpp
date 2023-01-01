#include "UIManager.h"

void UIManager::Update() {
	Collection::Update();

	for (auto& element : *GetAll()) {
		//auto s = static_cast<HealthBar<Monster>*>(element.second);
		//s->UpdateDirect();
		//s->RenderDirect();
		element.second->Update();
		element.second->Render();
	}
}

bool UIManager::OnMouseDown() {
	for (auto& element : *GetAll()) {
		if (!element.second->isInteractable) continue;
		// if mouse pos collides
		// return true and send onmousedown to that element
	}

	return false;
}