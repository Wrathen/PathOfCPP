#pragma once
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

class UIItem;
class UIElement {
public:
	typedef UIElement Super;

	UIElement(std::string texturePath = "assets/sprites/nosprite.png");
	virtual ~UIElement() {}

	GUID guid = 0;
	Transform transform;
	SpriteRenderer renderer;

	// A boolean to state that this element can be interacted with via Mouse Clicks or Mouse Hovers.
	bool isInteractable = false;
	// A boolean to state that this element was queued for deletion. Use frequently for validity checks in your codebase.
	bool isToBeDeleted = false;
	// Make the UIElement block raycasts so the mouse clicks don't go any more behind.
	bool isBlockingRaycasts = true;
	// Make the UIElement transient and not delete on scene changes.
	bool isToBeDeletedOnSceneChange = true;
	// You can disable automatic rendering that UIManager does and manually render on demand.
	bool isAutomaticRenderingDisabled = false;
	// Specifies whether UIItems can be applied into this UIElement.
	bool canItemsBeApplied = false;

	// Z-Index is used for sorting algorithm for who to draw in front of the other UIElements.
	// Bigger means that it has more priority.
	int zIndex = 0;

	// Base Functions
	virtual void Start();
	virtual void Update();
	virtual void Render();

	// Events
	// Returns a boolean to block raycasts
	virtual bool OnClick();
	// On an item applied to this specific UIElement.
	virtual bool OnApplyItem(UIItem* item);
	virtual void OnDelete() = 0;
	virtual void OnMouseEnter() = 0;
	virtual void OnMouseOver() = 0;
	virtual void OnMouseLeave() = 0;

	// Main Functions
	virtual void SetVisible(bool value);
	bool GetVisible ();
	void SetInteractable(bool value);
	void Delete();

	// Utility Functions
	void AssignGUID(GUID _guid);
	virtual std::string ToString();
};