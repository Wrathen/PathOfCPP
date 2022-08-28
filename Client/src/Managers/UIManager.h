#pragma once
#include "../UI/UIElement.h"
#include <unordered_map>
#include <vector>

#define UIMgr UIManager::GetInstance()
class UIManager {
public:
	static UIManager& GetInstance() {
		static UIManager instance;
		return instance;
	}

    void AddElement(UIElement* entity);
    void RemoveElement(UIElement* entity);
    UIElement* GetElement(GUID guid);

    void PrintAllElements();
    void UpdateAllElements();
    void RenderAllElements();

    bool OnMouseDown();

private:
    UIManager() {}
    ~UIManager();
    UIManager(UIManager const&) = delete;
    void operator=(UIManager const&) = delete;

    void DeleteElement(UIElement* element);
    void DeleteAllQueuedElements();

private:
	std::unordered_map<GUID, UIElement*> allElements;
    std::vector<UIElement*> toBeDeletedList;
};