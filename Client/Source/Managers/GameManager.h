#pragma once
#include <SDL.h>
#include <iostream>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Time.h"
#include "../Entities/Player.h"

#define GAME GameManager::GetInstance()
class GameManager: public Singleton<GameManager> {
	friend Singleton;
public:
	Player* player = nullptr;
	SDL_Event event{};

	int screenWidth = 1920;
	int screenHeight = 1080;
	int zoneWidth = 4000;
	int zoneHeight = 4000;
	bool isGameRunning = true;
	bool isGamePaused = false;

	// Base Functions
	void Init();
	void Update();
	void PollEvents();
	void Quit();
	void PauseGame(bool value);

	// Utility Functions
	Player* GetPlayer() const;
	int GetFPS() const;
	void DrawRect(int x, int y, int w, int h, SDL_Color color = { 0, 255, 0 });
	void DrawRect(Vector2 pos, int w, int h, SDL_Color color = { 0, 255, 0 });
	void DrawRect(Rect rect, SDL_Color color = { 0, 255, 0 });

private:
	GameManager() {}
	~GameManager() {}
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};