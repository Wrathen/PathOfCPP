#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Monsters/Zombie.h"
#include "../Entities/Monsters/Boar.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Collection.h"
#include "../Miscellaneous/Timer.h"

// Base Functions
void GameManager::Init() {
	MainRenderer.Init();
	Start();

	Collection<Monster> s();
}
void GameManager::Start() {
	player = new Player("Wrathen");
	new UIElement();

	// [To:Do] Delete--Debug
	for (int i = 0; i < 3000; ++i) {
		new Zombie("Zombie " + std::to_string(i));
		new Boar("Boar " + std::to_string(i));
	}

	Debug(player->ToString());

	Update();
}
void GameManager::Update() {
	// Count frames
	Uint64 frameStart, frameTime;

	while (GAME.isGameRunning) {
		Timer timer;
		frameStart = SDL_GetTicks64();

		// Main Stuff
		PollEvents();

		EntityMgr.Update();
		CollisionMgr.Update();
		Camera.Update();
		UIMgr.Update();
		
		MainRenderer.Draw();

		// Frame Timers, Delays
		frameTime = SDL_GetTicks64() - frameStart;
		//if (Time::FRAME_DELAY > frameTime) {
		//	SDL_Delay(Time::FRAME_DELAY - frameTime);
		//	frameTime = SDL_GetTicks64() - frameStart;
		//}

		Time::deltaTime = timer.GetTimeMS();
		Debug("FPS: " + std::to_string(1000.0f / Time::deltaTime) + ", MS: " + std::to_string(Time::deltaTime));
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