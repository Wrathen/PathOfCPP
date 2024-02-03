#pragma once

class Rect {
public:
	int x;
	int y;
	int w;
	int h;

	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};

	bool Intersects(const Rect& other) const;
	static bool IntersectsPoint(int x1, int y1, int w, int h, int x2, int y2);
	static bool IntersectsRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
};