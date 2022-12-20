#include "UIManager.h"

void UIManager::Update() {
	Collection::Update();
}

void UIManager::RenderAll() {
	auto* allElements = GetAll();
	for (auto& element : *allElements)
		element.second->Render();
}

bool UIManager::OnMouseDown() {
	auto* allElements = GetAll();
	for (auto& element : *allElements) {
		if (!element.second->isInteractable) continue;
		// if mouse pos collides
		// return true and send onmousedown to that element
	}

	return false;
}