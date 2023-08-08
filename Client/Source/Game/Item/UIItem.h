#pragma once
#include "Item.h"
#include "../../UI/UIElement.h"

class UIItem : public UIElement {
public:
	// Dropped item.
	Item* item = nullptr;
	
	// Constructor
	UIItem(Item* _item);
	
	// Base Functions
	void Start() override;
	void Update() override;
	void Render() override;

	// Events
	bool OnClick() override;
	void OnDelete() override;
	void OnMouseEnter() override;
	void OnMouseOver() override;
	void OnMouseLeave() override;
};