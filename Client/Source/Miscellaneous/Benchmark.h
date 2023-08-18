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
	template<typename Functor>
	void Execute(const char* name, Functor functor) {
		// Compile-time Error Handling ~~ Enforce that the Functor parameter is actually a lambda. Is there a better way to do this?
		// This sucks tbh. But let's keep it, it won't matter in runtime performance anyways.
		// Just trying to keep the programmer from using frequently used types in place of functor parameter.
		// Honestly, it'd not matter much if you just deleted the below two lines. Feel free to make a pull request on this, open for discussion.
		static constexpr bool isInvalidType = (!std::is_same<int, Functor>()
											&& !std::is_same<float, Functor>()
											&& !std::is_same<double, Functor>()
											&& !std::is_same<long, Functor>()
											&& !std::is_same<long long, Functor>()
											&& !std::is_same<const char*, Functor>()
											&& !std::is_same<std::string, Functor>());
		static_assert(isInvalidType, "Benchmark::Execute function requires a valid Lambda parameter such as [](){ foo(); }.");

		// Execute the lambda and store the time it took to process.
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
			std::cout << "[" << pair.first << "] -- " << pair.second << " us (" << (pair.second * 0.001f) << "ms)\n";
	}

	// Utility Functions
	std::vector<std::pair<const char*, long long>>& GetResults() { return benchmarkResults; }
};