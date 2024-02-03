#include <iomanip>
#include "GameManager.h"
#include "RenderManager.h"
#include "InputManager.h"
//#include "EntityManager.h"
#include "CameraManager.h"
#include "Core/Managers/SceneManager.h"
#include "Core/Managers/CollisionManager.h"
//#include "DatabaseManager.h"
//#include "UIManager.h"
//#include "UI/UserInterface.h"
#include "Core/Miscellaneous/Log.h"
#include "Core/Miscellaneous/Timer.h"
#include "Core/Miscellaneous/Benchmark.h"
//#include "Game/PowerUp/PowerUp.h"
//#include "Database/Item/ItemModifier.h"
#include "Game/Component/Components.h"
#include "Game/Scene/Scene.h"

// Base Functions
void GameManager::Init() {
	//DB.Init();
	MainRenderer.Init();
	//PowerUp::InitAllPowerUps();

	// Todo, read these from the Database.
	Core::SceneMgr.AddScenes({
		new Scene("Zone_Town.PZD", "Town"),
		new Scene("Zone_Forest.PZD", "Forest"),
		new Scene("Zone_DefiledCathedral (T16).PZD", "DefiledCathedral")
	});
	Core::SceneMgr.ChangeScene("Town");

	//UI.Init();
	Update();
}
void GameManager::Update() {
	// Count frames
	static Timer debugTimer{};
	static bool debugProfilerMsgEnabled = true;
	static bool limitFramerate = false;
	Timer frameTimer;
	double frameTime;

	Benchmark benchmark;
	benchmark.Add("PollEvents", [&] { PollEvents(); });
	benchmark.Add("MainRenderer.Clear", [] { MainRenderer.Clear(); });
	//benchmark.Add("CollisionMgr.Update", [] { CollisionMgr.Update(); });
	benchmark.Add("Scene.Update", [] { if (auto* currentScene = Core::SceneMgr.GetCurrentScene()) currentScene->Update(); });
	benchmark.Add("InputManager.Update", [] { InputMgr.Update(); });
	benchmark.Add("Camera.Update", [] { Camera.Update(); });
	//benchmark.Add("UserInterface.Update", [] { UI.Update(); }); // This also renders!
	benchmark.Add("MainRenderer.Draw", [] { MainRenderer.Draw(); });

	// Main Engine Loop
	while (GAME.isGameRunning) {
		// Execute all the main loop functions and benchmark them individually.
		benchmark.ExecuteAll();

		// Frame Timers, Delays
		frameTime = frameTimer.GetTimeMS();
		if (limitFramerate && Time::FRAME_DELAY > frameTime) {
			SDL_Delay(Time::FRAME_DELAY - (Uint32)frameTime);
			frameTime = frameTimer.GetTimeMS();
		}

		// Update Global Time variables.
		Time::frameTime = frameTime;
		Time::deltaTime = 1 / (1000.0f / frameTime);

		// Output Benchmarks
		if (debugProfilerMsgEnabled && debugTimer.GetTimeMS() > 2000) {
			benchmark.Log();
			debugTimer.Reset();
		}

		// Late-Update the Input Manager to handle input states.
		InputMgr.LateUpdate();

		// Late-Update the Scene
		if (Core::BaseScene* currentScene = Core::SceneMgr.GetCurrentScene())
			currentScene->LateUpdate();

		// Reset the Frame Timer.
		frameTimer.Reset();
	}
}
void GameManager::PollEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			GAME.Quit();
			break;
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				InputMgr.OnKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			InputMgr.OnKeyUp(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			InputMgr.OnMouseDown();
			break;
		case SDL_MOUSEBUTTONUP:
			InputMgr.OnMouseUp();
			break;
		}
	}
}
void GameManager::Quit() { GAME.isGameRunning = false; }
void GameManager::PauseGame(bool value) { isGamePaused = value; }

Core::Entity GameManager::GetLocalPlayer() {
	// If we already have a cached local player, return it.
	if (localPlayer)
		return localPlayer;

	// If we don't have a valid scene, we should return.
	auto* currentScene = Core::SceneMgr.GetCurrentScene();
	if (!currentScene) {
		Error("Invalid Current Scene.");
		return Core::Entity();
	}

	// Let's check if any entities in the scene has the LocalPlayerComponent.
	{
		auto view = currentScene->reg.view<LocalPlayerComponent>();
		int amountOfComponents = view.size();

		if (amountOfComponents != 0) {
			if (amountOfComponents > 1)
				Warn("Multiple LocalPlayerComponents found in the current scene!");

			localPlayer = Core::Entity(currentScene, view.front());
		}
	}

	// No local player component was found. 
	// Then we should go through all the PlayerComponents and pick the first one as the local one.
	{
		auto view = currentScene->reg.view<PlayerComponent>();
		int amountOfComponents = view.size();

		if (amountOfComponents == 0) {
			Error("No player was found in the current scene.");
			return Core::Entity();
		}

		localPlayer = Core::Entity(currentScene, view.front());
	}

	return localPlayer;
}