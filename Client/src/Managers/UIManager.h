#pragma once
#include <unordered_map>
#include <vector>
#include "../UI/UIElement.h"
#include "../Miscellaneous/Collection.h"
#include "../Miscellaneous/Singleton.h"

#define UIMgr UIManager::GetInstance()
class UIManager: public Collection<UIElement>, public Singleton<UIManager> { friend class Singleton;
public:
	UIElement* currentHoveredElement = nullptr;
	void Update();
    bool OnMouseDown();
	void OnMouseMove();

private:
	UIManager() : Collection<UIElement>(100000) {}
	~UIManager() {};
	UIManager(UIManager const&) = delete;
	void operator=(UIManager const&) = delete;
};