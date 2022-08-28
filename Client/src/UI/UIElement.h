#pragma once
#include <string>
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

class UIElement {
	friend class UIManager;
public:
	// Base Functions
	virtual void Start();
	virtual void Update();
	virtual void Render();

	// Main Functions
	void Delete();

	// Utility Functions
	virtual std::string ToString() {
		if (!this) return "This UIElement has already been deleted. What are you doing?!";
		return "UIElement with GUID: " + std::to_string(guid);
	}

private:
	void AssignGUID(GUID guid) { this->guid = guid; }

public:
	UIElement(std::string texturePath = "assets/sprites/nosprite.png");

	GUID guid = 0;
	Transform transform;
	SpriteRenderer renderer;
};