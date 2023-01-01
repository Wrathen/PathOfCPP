#pragma once
#include "Collider.h"

class BoxCollider: public Collider {
public:
	int w = 0;
	int h = 0;
	int xOffset = 0;
	int yOffset = 0;

	void SetProperties(int _w, int _h, int _xOffset = 0, int _yOffset = 0);

	bool Intersects(const BoxCollider& other) const;
	void OnCollisionEnter(Collider* other) override;
};