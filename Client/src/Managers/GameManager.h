#pragma once
#include <SDL.h>
#include <iostream>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Time.h"
#include "../Entities/Player.h"

#define GAME GameManager::GetInstance()
class GameManager: public Singleton<GameManager> { friend class Singleton;
public:
	Player* player = nullptr;
	SDL_Event event {};

	int gameWidth = 1920;
	int gameHeight = 1080;
	bool isGameRunning = true;
	bool isGamePaused = false;

	// Base Functions
	void Init();
	void Update();
	void PollEvents();
	void Quit();
	void PauseGame(bool value);

	// Main Functions
	Player* GetPlayer() const;
	void DrawRect(int x, int y, int w, int h);
	void DrawRect(Vector2 pos, int w, int h);

private:
	GameManager() {}
	~GameManager() {}
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};