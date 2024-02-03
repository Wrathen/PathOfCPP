#pragma once
#include <SDL.h>
#include <iostream>
#include "Core/Miscellaneous/Time.h"
#include "Core/Miscellaneous/Vector.h"
#include "Core/Game/Entity/Entity.h"

#define GAME GameManager::GetInstance()
class GameManager {
public:
	static GameManager& GetInstance() { static GameManager _i; return _i; }

	SDL_Event event{};
	Core::Entity localPlayer;

	bool isGameRunning = true;
	bool isGamePaused = false;

	// Base Functions
	void Init();
	void Update();
	void PollEvents();
	void Quit();
	void PauseGame(bool value);

	// Utility Functions
	Core::Entity GetLocalPlayer();

private:
	GameManager() {}
	~GameManager() {}
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};