#include "UIManager.h"

void UIManager::Update() {
	Collection::Update();

	for (auto& element : *GetAll()) {
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