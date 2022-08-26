#pragma once

#define Rand Random::GetInstance()
#define RandomInt Random::GetInstance().Next
#include <random>
#include <ctime>
#include <chrono>

// [To:Do] This random class is so bad, it's like necromancer ascendancy after the recent changes.
// Either implement or yoink a good one.
class Random
{
public:
	static Random& GetInstance() {
		static Random instance;
		return instance;
	}

	int Next(int max = 9999999) {
		i *= 1.03f;
		srand(++i);

		return rand() % max;
	}

	unsigned int i = 0;
};