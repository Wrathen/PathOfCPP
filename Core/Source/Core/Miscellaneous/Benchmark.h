#pragma once
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <iomanip>
#include "Time.h"
#include "Timer.h"

class Benchmark {
public:
	// Pairs (<name, function> --- <name, elapsedTime>) of vectors.
	std::vector<std::pair<const char*, std::function<void()>>> allFuncs;
	std::vector<std::pair<const char*, long long>> benchmarkResults;

	// Add a Lambda Function to the list.
	void Add(const char* name, std::function<void()> functor) {
		allFuncs.push_back(std::make_pair(name, functor));
	}

	// Execute a single function and store the benchmark result.
	void Execute(const char* name, std::function<void()> functor) {
		Timer timer;
		functor();
		timer.Pause();
		benchmarkResults.push_back(std::make_pair(name, timer.GetTime()));
	}

	// Executes all the added functions at once and store the benchmark results. 
	// This clears the benchmark results beforehand.
	void ExecuteAll() {
		benchmarkResults.clear();

		for (auto& func : allFuncs) {
			Timer timer;
			func.second();
			timer.Pause();
			benchmarkResults.push_back(std::make_pair(func.first, timer.GetTime()));
		}
	}

	// Log the general purpose Performance info and benchmark results of each function added.
	void Log() {
		std::cout << "<----------------------------------------------------->" << std::endl;
		std::cout << std::setprecision(2) << std::fixed << 
			("##### FPS: " + std::to_string(1000.0f / Time::frameTime) +
			", FrameTime: " + std::to_string(Time::frameTime)) +
			", DeltaTime: " + std::to_string(Time::deltaTime) << std::endl;
		std::cout << "<----------------------------------------------------->" << std::endl;

		for (auto& pair : benchmarkResults)
			std::cout << "[" << pair.first << "] -- " << pair.second << " us (" << (pair.second * 0.001f) << "ms)\n";
	}
};