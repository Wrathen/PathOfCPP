#include <iomanip>
#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "DatabaseManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "../UI/UserInterface.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Timer.h"
#include "../Miscellaneous/Benchmark.h"
#include "../Game/PowerUp/PowerUp.h"
#include "../Database/Item/ItemModifier.h"

// Base Functions
void GameManager::Init() {
	DB.Init();
	MainRenderer.Init();
	SceneMgr.Init();
	PowerUp::InitAllPowerUps();

	// These stuff are temporary.
	{
		player = new Player("Wrathen");
		SceneMgr.ChangeScene("Town");
	}

	UI.Init();
	Update();
}
void GameManager::Update() {
	// Count frames
	static Timer debugTimer{};
	static bool debugProfilerMsgEnabled = true;
	static bool limitFramerate = false;
	Timer frameTimer;
	float frameTime;

	Benchmark benchmark;
	benchmark.Add("PollEvents", [&] { PollEvents(); });
	benchmark.Add("MainRenderer.Clear", [] { MainRenderer.Clear(); });
	benchmark.Add("CollisionMgr.Update", [] { CollisionMgr.Update(); });
	benchmark.Add("Scene.Update", [] { if (Scene* currentScene = SceneMgr.GetCurrentScene()) currentScene->Update(); });
	benchmark.Add("InputManager.Update", [] { InputMgr.Update(); });
	benchmark.Add("Camera.Update", [] { Camera.Update(); });
	benchmark.Add("UserInterface.Update", [] { UI.Update(); }); // This also renders!
	benchmark.Add("MainRenderer.Draw", [] { MainRenderer.Draw(); });

	// Main Engine Loop
	while (GAME.isGameRunning) {
		// Execute all the main loop functions and benchmark them individually.
		benchmark.ExecuteAll();

		// Frame Timers, Delays
		frameTime = frameTimer.GetTimeMS();
		if (limitFramerate && Time::FRAME_DELAY > frameTime) {
			SDL_Delay(Time::FRAME_DELAY - frameTime);
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
		if (Scene* currentScene = SceneMgr.GetCurrentScene()) 
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

// Utility Functions
Player* GameManager::GetPlayer() const { return player; }
int GameManager::GetFPS() const { return 1.0f / Time::deltaTime; }
void GameManager::DrawRect(int x, int y, int w, int h, SDL_Color color) {
	SDL_Rect rect{ x, y, w, h };
	SDL_SetRenderDrawColor(MainRenderer.renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(MainRenderer.renderer, &rect);
}
void GameManager::DrawRect(Vector2 pos, int w, int h, SDL_Color color) { DrawRect(pos.x, pos.y, w, h, color); }
void GameManager::DrawRect(Rect rect, SDL_Color color) { DrawRect(rect.x, rect.y, rect.w, rect.h, color); }