#pragma once

class Rect {
public:
	int x;
	int y;
	int w;
	int h;

	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
	
	bool Intersects(const Rect& other) const;
};