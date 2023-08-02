#pragma once
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

class UIElement {
public:
	typedef UIElement Super;

	UIElement(std::string texturePath = "assets/sprites/nosprite.png");
	virtual ~UIElement() {}

	GUID guid = 0;
	Transform transform;
	SpriteRenderer renderer;

	bool isInteractable = false;
	bool isToBeDeleted = false;
	bool isBlockingRaycasts = true;
	bool isToBeDeletedOnSceneChange = true;
	bool isAutomaticRenderingDisabled = false;

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