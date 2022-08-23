#pragma once
#include <SDL.h>
#include <iostream>
#include "../Miscellaneous/Time.h"
#include "../Entities/Player.h"

#define GAME GameManager::GetInstance()
class GameManager {
public:
	static GameManager& GetInstance() {
		static GameManager instance;
		return instance;
	}

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

public:
	SDL_Event event;
	bool isGameRunning = true;
	Player* player;
};