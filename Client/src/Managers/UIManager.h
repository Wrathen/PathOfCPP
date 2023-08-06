#pragma once
#include <unordered_map>
#include <vector>
#include "../UI/UIElement.h"
#include "../Miscellaneous/Collection.h"
#include "../Miscellaneous/Singleton.h"
#include "../Game/Item/UIItem.h"

#define UIMgr UIManager::GetInstance()
class UIManager: public Collection<UIElement>, public Singleton<UIManager> { friend class Singleton;
public:
	// Current UIElement that is being mouse-hovered.
	UIElement* currentHoveredElement = nullptr;
	// Current Item that you hold in your hand.
	UIItem* currentHeldItem = nullptr;
	
	void Update();
    bool OnMouseDown();
	void OnMouseMove();

	// Pick up an item and place it into your hand/cursor. Feel free to suggest a new name for this, I hesitated on this.
	void PickItemToHand(UIItem* item);

private:
	UIManager() : Collection<UIElement>(100000) {}
	~UIManager() {};
	UIManager(UIManager const&) = delete;
	void operator=(UIManager const&) = delete;
};