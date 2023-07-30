#pragma once
#include <random>
#include <chrono>
#include <ctime>
#include <cassert>
#include "Singleton.h"
#include "Vector.h"
#include "Log.h"

class Random : public Singleton<Random> {
private:
	std::mt19937 rng;
	unsigned int _seed = 0;

	void SetSeed_Internal(unsigned int seed = 0) {
		rng.seed(seed ? seed : (unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		_seed = seed;
	}
	void RandomizeSeed(int value) {
		if (_seed == 0) return;
		SetSeed_Internal(value);
	}

public:
	Random(unsigned int seed = 0) { SetSeed_Internal(seed); }
	int Next(int min, int max) {
		if (min >= max) max = min + 1;
		std::uniform_int_distribution<int> uni(min, max - 1);

		int randomValue = uni(rng);
		RandomizeSeed(randomValue);

		return randomValue;
	}
	float Next(float min, float max) {
		if (min >= max) max = min + 0.00001f;
		std::uniform_real_distribution<float> uni(min, max);

		float randomValue = uni(rng);
		RandomizeSeed((int)randomValue);

		return randomValue;
	}
	Vector2 NextVector2(float radius) {
		float angle = Next(-3.1415f, 3.1415f);
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;

		return Vector2(x, y);
	}
	Vector2 NextVector2(float x, float y) { return Vector2(Next(0.0f, x), Next(0.0f, y)); }

	template <typename T>
	T Next(T count) { return static_cast<T>(Next(0, (int)count)); }

	// Static function to set seed.
	static void SetSeed(unsigned int seed) { Random::GetInstance().SetSeed_Internal(seed); }
};

// Returns an integer between min [inclusive] and max [exclusive].
static int RandomInt(int min, int max) { return Random::GetInstance().Next(min, max); }

// Returns a float between min [inclusive] and max [inclusive].
static float RandomFloat(float min, float max) { return Random::GetInstance().Next(min, max); }

// Returns a random Vector in a given radius.
static Vector2 RandomVector(float radius) { return Random::GetInstance().NextVector2(radius); }

// Returns a random Vector in a given radius.
static Vector2 RandomVector(float x, float y) { return Random::GetInstance().NextVector2(x, y); }

// Returns a random entry from an Enum. Assumes enumerator starts from <0> inclusive and goes to <count> exclusive.
template <typename T>
static T RandomEnum(T count) { return Random::GetInstance().Next(count); }

// <------------------------------------------------->
// <--------------- Weighted Random ----------------->
// <------------------------------------------------->
template <typename T>
class WeightedRandom {
	std::vector<T> items;
	std::vector<uint32_t> weights;
	uint32_t maxWeight = 0;
	uint32_t totalWeight = 0;

public:
	WeightedRandom() = default;
	WeightedRandom(std::vector<T> _items, std::vector<uint32_t> _weights) {
		// Vector sizes have to match.
		assert(_items.size() == _weights.size());
		
		// For each element in the parameter vector, add them into our lists.
		for (size_t i = 0; i < _items.size(); ++i)
			Add(_items[i], _weights[i]);
	}

	T GetRandom() {
		int randomWeight = RandomInt(0, totalWeight);
		for (size_t i = 0; i < weights.size(); ++i) {
			randomWeight -= weights[i];
			if (randomWeight < 1)
				return items[i];
		}

		// This should never happen.
		assert(1);
		return items[0];
	}

	void Add(T item, uint32_t weight) {
		// Update Total & Max Weights
		totalWeight += weight;
		if (weight > maxWeight)
			maxWeight = weight;

		// Add the item and weight into the table.
		items.push_back(item);
		weights.push_back(weight);
	}
};