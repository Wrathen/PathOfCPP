#include <iomanip>
#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "../UI/UserInterface.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Timer.h"
#include "../Game/PowerUp/PowerUp.h"

// Utility functions, will move them out of here/class.
void GameManager::DrawRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(MainRenderer.renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(MainRenderer.renderer, &rect);
}
void GameManager::DrawRect(Vector2 pos, int w, int h) { DrawRect(pos.x, pos.y, w, h); }

// Base Functions
void GameManager::Init() { 
	MainRenderer.Init();
	SceneMgr.Init();
	PowerUp::InitAllPowerUps();

	player = new Player("Wrathen");
	SceneMgr.ChangeScene("Town");

	UI.Init();
	Update();
}
void GameManager::Update() {
	// Count frames
	static Timer debugTimer{};
	static bool debugProfilerMsgEnabled = true;
	Timer timer;
	float frameTime;

	while (GAME.isGameRunning) {
		// Main Loop
		Timer benchmark1("PollEvents");
		PollEvents();
		benchmark1.Pause();

		Timer benchmark2("MainRenderer.Clear");
		MainRenderer.Clear();
		benchmark2.Pause();

		Timer benchmark3("Scene.Update");
		Scene* currentScene = SceneMgr.GetCurrentScene();
		if (!currentScene) {
			Warn("SCENE NOT FOUND!");
			//continue;
		}
		currentScene->Update();
		benchmark3.Pause();

		Timer benchmark4("EntityMgr.Update");
		EntityMgr.Update(); // This also renders!
		benchmark4.Pause();

		Timer benchmark5("CollisionMgr.Update");
		if (!isGamePaused) CollisionMgr.Update();
		benchmark5.Pause();

		Timer benchmark6("Camera.Update");
		Camera.Update();
		benchmark6.Pause();

		Timer benchmark7("InputManager.Update");
		InputMgr.Update();
		benchmark7.Pause();

		Timer benchmark8("UIMgr.Update");
		UIMgr.Update(); // This also renders!
		benchmark8.Pause();

		Timer benchmark9("UserInterface.Update");
		UI.Update(); // This also renders!
		benchmark9.Pause();

		Timer benchmark10("MainRenderer.Draw");
		MainRenderer.Draw();
		benchmark10.Pause();

		// Frame Timers, Delays
		bool limitFramerate = false;
		frameTime = timer.GetTimeMS();
		if (limitFramerate && Time::FRAME_DELAY > frameTime) {
			SDL_Delay(Time::FRAME_DELAY - frameTime);
			frameTime = timer.GetTimeMS();
		}

		Time::deltaTime = frameTime;

		// Debug Stuff
		if (debugTimer.GetTimeMS() > 1500) {
			if (debugProfilerMsgEnabled) {
				std::cout << "<----------------------------------------------------->" << std::endl;
				std::cout << std::setprecision(2) << std::fixed << ("##### FPS: " + std::to_string(1000.0f / Time::deltaTime) +
					", MS: " + std::to_string(Time::deltaTime)) +
					", Amount of Entities: " + std::to_string(EntityMgr.GetAll()->size()) +
					", TotalKilledEnemies: " + std::to_string(GetPlayer()->stats->totalKills) +
					", NumberOfProjectiles: " + std::to_string(GetPlayer()->stats->GetNumberOfProjectiles()) << std::endl;
				std::cout << "<----------------------------------------------------->" << std::endl;

				benchmark1.Log();
				benchmark2.Log();
				benchmark3.Log();
				benchmark4.Log();
				benchmark5.Log();
				benchmark6.Log();
				benchmark7.Log();
				benchmark8.Log();
				benchmark9.Log();
				benchmark10.Log();
			}
			debugTimer.Reset();
		}

		// Late-Update the Scene
		if (currentScene) currentScene->LateUpdate();
		timer.Reset();
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

// Main Functions
Player* GameManager::GetPlayer() const { return player; }