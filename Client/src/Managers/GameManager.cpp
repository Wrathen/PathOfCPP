#include <iomanip>
#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "EnemySpawnManager.h"
#include "UIManager.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Timer.h"

// Base Functions
void GameManager::Init() {
	MainRenderer.Init();
	Start();
}
void GameManager::Start() {
	player = new Player("Wrathen");
	new UIElement();

	Debug(player->ToString());

	Update();
}
void GameManager::Update() {
	static Timer debugTimer{};

	// Count frames
	Timer timer;
	float frameTime;

	while (GAME.isGameRunning) {
		timer.Reset();

		// Main Loop
		PollEvents();
		MainRenderer.Clear();
		EnemySpawner.Update();
		EntityMgr.Update(); // This also renders!
		player->Update();
		CollisionMgr.Update();
		Camera.Update();
		UIMgr.Update(); // This also renders!
		MainRenderer.Draw();

		// Frame Timers, Delays
		bool limitFramerate = false;
		frameTime = timer.GetTimeMS();
		if (limitFramerate && Time::FRAME_DELAY > frameTime) {
			SDL_Delay(Time::FRAME_DELAY - frameTime);
			frameTime = timer.GetTimeMS();
		}

		Time::deltaTime = frameTime;

		// Debug Stuff
		if (debugTimer.GetTimeMS() > 300) {
			debugTimer.Reset();
			std::cout << std::setprecision(2) << std::fixed << ("FPS: " + std::to_string(1000.0f / Time::deltaTime) +
				", MS: " + std::to_string(Time::deltaTime)) +
				", TotalSpawnedEnemies: " + std::to_string(EnemySpawner.totalNumberOfSpawnedEnemies) +
				", TotalKilledEnemies: " + std::to_string(GetPlayer()->totalKills) +
				", NumberOfProjectiles: " + std::to_string(GetPlayer()->GetNumberOfProjectiles()) << std::endl;
		}
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

// Main Functions
Player* GameManager::GetPlayer() const { return player; }