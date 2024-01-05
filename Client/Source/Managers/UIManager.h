#pragma once
#include <unordered_map>
#include <vector>
#include "../UI/UIElement.h"
#include "../Miscellaneous/Collection.h"
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Mouse.h"
#include "../Miscellaneous/Point.h"
#include "../Game/Item/UIItem.h"

#define UIMgr UIManager::GetInstance()
class UIManager: public Collection<UIElement>, public Singleton<UIManager> { friend class Singleton;
public:
	// Current UIElement that is being mouse-hovered.
	std::shared_ptr<UIElement> currentHoveredElement = nullptr;
	// Current Item that you hold in your hand.
	UIItem* currentHeldItem = nullptr;
	
	void Update();
	void UpdateCollection();
    bool OnMouseDown();
	void OnMouseMove();

	template <typename T>
	bool HandleMouseDown(std::vector<T>& elementVector) {
		// Get Mouse Position
		Point mousePos = Mouse::GetPosition().ToPoint();

		// Iterate over all viable elements and send them the OnClick event.
		for (auto& element : elementVector) {
			if (!element || !element->isInteractable || element->isToBeDeleted) continue;
			auto target = element;

			Vector2 targetPos = target->transform.GetScreenPosition();
			auto targetWidth = target->renderer.width;
			auto targetHeight = target->renderer.height;
			Rect targetCollider{(int)targetPos.x, (int)targetPos.y, (int)targetWidth, (int)targetHeight};

			// If it gets offsetted by getting drawn centered, we should offset back.
			if (target->renderer.shouldDrawCentered) {
				targetCollider.x -= targetWidth / 2;
				targetCollider.y -= targetHeight / 2;
			}

			if (mousePos.Intersects(targetCollider)) {
				bool raycastBlocked = target->OnClick();
				if (raycastBlocked) return true;
			}
		}

		// Return false, indicating further raycasts are not blocked.
		return false;
	}

	// Pick up an item and place it into your hand/cursor. Feel free to suggest a new name for this, I hesitated on this.
	void PickItemToHand(UIItem* item);

private:
	UIManager() : Collection<UIElement>(100000) {}
	~UIManager() {};
	UIManager(UIManager const&) = delete;
	void operator=(UIManager const&) = delete;
};