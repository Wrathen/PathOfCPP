#pragma once
#include <vector>
#include <functional>
#include <string>
#include "Timer.h"

class Benchmark {
public:
	// pair of <Name of Benchmark, Time it took to execute>.
	std::vector<std::pair<const char*, long long>> benchmarkResults;

	// Accepts Lambda Function
	void Execute(const char* name, void(*functor)()) {
		Timer timer;
		functor();
		timer.Pause();
		benchmarkResults.push_back(std::make_pair(name, timer.GetTime()));
	}

	void Log() {
		std::cout << "<----------------------------------------------------->" << std::endl;
		std::cout << std::setprecision(2) << std::fixed << ("##### FPS: " + std::to_string(1000.0f / Time::frameTime) +
			", FrameTime: " + std::to_string(Time::frameTime)) +
			", DeltaTime: " + std::to_string(Time::deltaTime) +
			", Amount of Entities: " + std::to_string(EntityMgr.GetAll()->size()) +
			", TotalKilledEnemies: " + std::to_string(GAME.GetPlayer()->CStats->totalKills) +
			", NumberOfProjectiles: " + std::to_string(GAME.GetPlayer()->CStats->GetNumberOfProjectiles()) << std::endl;
		std::cout << "<----------------------------------------------------->" << std::endl;

		for (auto& pair : benchmarkResults)
			std::cout << "[" << pair.first << "] -- " << pair.second << " us (" << (pair.second*0.001f) << "ms)\n";
	}

	// Utility Functions
	std::vector<std::pair<const char*, long long>>& GetResults() { return benchmarkResults; }
};