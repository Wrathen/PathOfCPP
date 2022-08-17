#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Monster.h"

// Base Functions
void GameManager::Init() {
	MainRenderer.Init();
	Start();
}
void GameManager::Start() {
	player = new Player("Wrathen");
	Monster* finallyAVisibleMonster = new Monster("assets/monster.png", "Zombie");

	// [To:Do] Delete--Debug
	for (int i = 0; i < 500; ++i) {
		new Monster("assets/monster.png", "Zombie");
		new Monster("assets/monster2.png", "Boar");
	}

	GAME.Debug(player->ToString());
	GAME.Debug(finallyAVisibleMonster->ToString());

	Update();
}
void GameManager::Update() {
	// Count frames
	Uint64 frameStart, frameTime;

	while (GAME.isGameRunning) {
		frameStart = SDL_GetTicks64();
		
		// Main Stuff
		PollEvents();
		Camera.Update();
		EntityMgr.UpdateAllEntities();
		MainRenderer.Draw();

		// Frame Timers, Delays
		frameTime = SDL_GetTicks() - frameStart;
		if (Time::FRAME_DELAY > frameTime) {
			SDL_Delay(Time::FRAME_DELAY - frameTime);
			frameTime = SDL_GetTicks() - frameStart;
		}

		// Update deltaTime
		Time::deltaTime = 1.0f / frameTime;

		Debug("FPS: " + std::to_string(1000/(frameTime == 0 ? 1 : frameTime)));
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
		}
	}
}
void GameManager::Quit() { GAME.isGameRunning = false; }

// Main Functions
void GameManager::Debug(std::string_view msg) {
	std::cout << msg << std::endl;
}
Player* GameManager::GetPlayer() const { return player; }