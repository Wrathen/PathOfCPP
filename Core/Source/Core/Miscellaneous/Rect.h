#pragma once

// A really small struct (1 byte) that can be used for receiving information about a collision query result.
struct CollisionResult {
	inline static char NONE = 0b0000;
	inline static char LEFT = 0b0001;
	inline static char RIGHT = 0b0010;
	inline static char TOP = 0b0100;
	inline static char BOTTOM = 0b1000;

	inline bool Horizontal() { return Left() || Right(); }
	inline bool Vertical() { return Top() || Bottom(); }
	inline bool Left() { return result & LEFT; }
	inline bool Right() { return result & RIGHT; }
	inline bool Top() { return result & TOP; }
	inline bool Bottom() { return result & BOTTOM; }

	// Returns a boolean that indicates a collision's presence. True: collision happened.
	constexpr operator bool() { return result != NONE; }

	CollisionResult operator|(char flag) { result |= flag; return *this; }
	void operator|=(char flag) { result |= flag; }

	CollisionResult() = default;
	CollisionResult(char _result) : result(_result) {}

private:
	char result = 0b0000;
};

class Rect {
public:
	int x;
	int y;
	int w;
	int h;

	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};

	CollisionResult Intersects(const Rect& other) const;
	static inline bool IntersectsPoint(int x1, int y1, int w, int h, int x2, int y2);
	static inline CollisionResult IntersectsRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
};