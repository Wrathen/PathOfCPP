#pragma once
#include <unordered_map>
#include <vector>
#include "../UI/UIElement.h"
#include "../Miscellaneous/Collection.h"
#include "../Miscellaneous/Singleton.h"

#define UIMgr UIManager::GetInstance()
class UIManager: public Collection<UIElement>, public Singleton<UIManager> { friend class Singleton;
public:
	void Update();
    bool OnMouseDown();

private:
	UIManager() : Collection<UIElement>(100000) {}
	~UIManager() {};
	UIManager(UIManager const&) = delete;
	void operator=(UIManager const&) = delete;
};