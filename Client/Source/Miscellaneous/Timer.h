#pragma once
#include <chrono>
#include <string>
#include <iostream>

typedef std::chrono::high_resolution_clock cclock;

class Timer {
private:
	std::string name;
	std::chrono::time_point<cclock> initTime;
	long long duration = 0;
	bool isPaused = false;

public:
	// Constructors
	Timer() : Timer("Unnamed Timer") {}
	Timer(std::string _name) : name(_name) { initTime = cclock::now(); }

	// Main Functions
	void Continue() { isPaused = false; }
	void Pause() { duration = GetTime(); isPaused = true; }
	void Reset() { initTime = cclock::now(); }
	void Log() {
		if (!isPaused) duration = GetTime();
		double ms = duration * 0.001;

		std::cout << name << " -- " << duration << " us (" << ms << "ms)" << std::endl;
	}

	// Utility Functions
	double GetTimeMS() { return GetTime() * 0.001; }
	long long GetTime() {
		auto curTime = cclock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(initTime).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(curTime).time_since_epoch().count();

		return end - start;
	}
};