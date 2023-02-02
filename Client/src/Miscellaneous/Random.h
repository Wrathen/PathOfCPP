#pragma once
#include <random>
#include <chrono>
#include <ctime>
#include "Singleton.h"
#include "Vector.h"

//#define Rand Random::GetInstance()

class Random : public Singleton<Random> {
private:
	static std::mt19937 rng;

	// Static member initialization function to seed the random number generator with the current time
	static std::mt19937& GetRNG() {
		static std::mt19937 rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
		return rng;
	}

public:
	static int Next(int min, int max) {
		if (min >= max) max = min + 1;
		std::uniform_int_distribution<int> uni(min, max - 1);
		return uni(GetRNG());
	}
	static float Next(float min, float max) {
		if (min >= max) max = min + 0.00001f;
		std::uniform_real_distribution<float> uni(min, max);
		return uni(GetRNG());
	}
};

// Returns an integer between min [inclusive] and max [exclusive].
static int RandomInt(int min, int max) { return Random::GetInstance().Next(min, max); }

// Returns an integer between 0 [inclusive] and max [exclusive].
static int RandomInt(int max) { return Random::GetInstance().Next(0, max); }

// Returns a float between min [inclusive] and max [inclusive].
static float RandomFloat(float min, float max) { return Random::GetInstance().Next(min, max); }

// Returns a float between 0 [inclusive] and max [inclusive].
static float RandomFloat(float max) { return Random::GetInstance().Next(0.0f, max); }

// Returns a random Vector in a given radius.
static Vector2 RandomVector(float radius) {
	float angle = RandomFloat(3.1415f);
	float x = cos(angle) * radius;
	float y = sin(angle) * radius;
	return Vector2(x, y);
}

// Returns a random entry from an Enum. 
// Assumes enumerator starts from <0> inclusive and goes to <count> exclusive.
template <typename T>
static T RandomEnum(T count) {
	return static_cast<T>(RandomInt((int)count));
}