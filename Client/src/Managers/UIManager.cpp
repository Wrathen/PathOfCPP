#include "UIManager.h"
#include <string>
#include "../Miscellaneous/Log.h"

// Main Functions
void UIManager::AddElement(UIElement* element) {
	if (!element) return;

	static GUID guid;
	element->AssignGUID(guid);
	allElements[guid++] = element;
}
void UIManager::RemoveElement(UIElement* element) { if (element) toBeDeletedList.push_back(element); }
void UIManager::DeleteElement(UIElement* element) {
	if (!element) return;
	
	allElements.erase(element->guid);

	//Debug("Deleted " + element->ToString());
	delete element;
}
UIElement* UIManager::GetElement(GUID guid) {
	auto element = allElements.find(guid);
	return element != allElements.end() ? element->second : nullptr;
}

// Main Loop&Utility
void UIManager::DeleteAllQueuedElements() {
	for (auto it = toBeDeletedList.rbegin(); it != toBeDeletedList.rend(); ++it) DeleteElement(*it);
	toBeDeletedList.clear();
}
void UIManager::PrintAllElements() {
	for (auto& element : allElements)
		Debug(element.second->ToString());
}
void UIManager::UpdateAllElements() {
	DeleteAllQueuedElements();

	for (auto& element : allElements)
		element.second->Update();
}
void UIManager::RenderAllElements() {
	for (auto& element : allElements)
		element.second->Render();
}

bool UIManager::OnMouseDown() {
	// get mouse pos
	for (auto& element : allElements) {
		if (!element.second->isInteractable) continue;
		// if mouse pos collides
		// return true and send onmousedonw to that element
	}

	return false;
}

UIManager::~UIManager() {
	for (auto& element : allElements) delete element.second;
	allElements.clear();
}