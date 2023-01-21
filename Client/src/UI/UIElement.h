#pragma once
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

class UIElement {
public:
	UIElement(std::string texturePath = "assets/sprites/nosprite.png");
	virtual ~UIElement() {}

	GUID guid = 0;
	Transform transform;
	SpriteRenderer renderer;

	bool isInteractable = true;
	bool isToBeDeleted = false;
	bool isBlockingRaycasts = true;
	bool isToBeDeletedOnSceneChange = true;
	bool isAutomaticRenderingDisabled = false;

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
	void SetInteractable(bool value);
	void Delete();

	// Utility Functions
	void AssignGUID(GUID _guid);
	virtual std::string ToString();
};