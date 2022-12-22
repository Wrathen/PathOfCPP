#pragma once
#include <SDL.h>
#include <iostream>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Time.h"
#include "../Entities/Player.h"


#define GAME GameManager::GetInstance()
class GameManager: public Singleton<GameManager> { friend class Singleton;
public:
	SDL_Event event;
	Player* player;

	int gameWidth = 1920;
	int gameHeight = 1080;
	bool isGameRunning = true;

	// Base Functions
	void Init();
	void Start();
	void Update();
	void PollEvents();
	void Quit();

	// Main Functions
	Player* GetPlayer() const;

private:
	GameManager() {}
	~GameManager() {}
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};