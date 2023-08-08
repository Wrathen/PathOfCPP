#pragma once
#include "Collider.h"

class BoxCollider: public Collider {
public:
	int w = 16;
	int h = 16;

	// Setters and Getters
	void SetWidth(int _w);
	void SetHeight(int _h);
	Rect GetBoundaries();
	
	// Main Functions
	bool Intersects(const BoxCollider& other) const;
	void OnCollisionEnter(Collider* other) override;
};