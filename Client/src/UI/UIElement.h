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

	// Base Functions
	virtual void Start();
	virtual void Update();
	virtual void Render();

	// Main Functions
	void SetInteractable(bool value) { isInteractable = value; }
	void Delete();

	// Utility Functions
	void AssignGUID(GUID _guid) { if (guid != 0) return; guid = _guid; }
	virtual std::string ToString() {
		if (!this) return "This UIElement has already been deleted. What are you doing?!";
		return "UIElement with GUID: " + std::to_string(guid);
	}
};