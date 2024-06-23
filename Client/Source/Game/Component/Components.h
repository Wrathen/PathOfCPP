#pragma once
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "Core/Game/Component/Components.h"
#include "Core/Miscellaneous/Vector.h"

struct LocalPlayerComponent {
	float gold = 0;
};
struct TextureComponent {
	SDL_Texture* texture = nullptr;

	TextureComponent() = default;
	TextureComponent(const TextureComponent&) = default;
	TextureComponent(SDL_Texture* _texture) : texture(_texture) {}
};

struct SpriteRendererComponent {
	SDL_Rect srcRect = { 0, 0, 0, 0 };
	SDL_Rect destRect = { 0, 0, 0, 0 };

	SDL_Color color = { 255, 255, 255, 255 };

	Vector2 sourceOffset{ 0, 0 };
	Vector2 offset{ 0, 0 };
	Vector2 localScale{ 1.0f, 1.0f };

	int width = 32;
	int height = 32;

	// Higher = front
	int32_t zIndex = 0;

	bool isFlipped = false;
	bool isVisible = true;
	bool isAbsolutePositioned = false;
	bool shouldDrawCentered = true;

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent&) = default;
	SpriteRendererComponent(SDL_Point dimensions) : width(dimensions.x), height(dimensions.y) {}
};

struct TextRendererComponent {
	std::string _text;
	unsigned int _size{ 16 };

	// Shadows
	SDL_Color shadowColor = { 0, 0, 0, 255 };
	unsigned int shadowSize = 0;
	bool isShadowEnabled = false;
};

struct HealthBarComponent {
	Vector2 offset;
};

struct NameTagComponent {
	Vector2 offset;
};

struct AnimationComponent {
	std::string name = "Idle";
	int lengthMS = 333;
	float speedMultiplier = 1.0f;

	int spriteWidth = 32;
	int spriteHeight = 32;
	int currentX = 0;
	int currentY = 0;
	int minCellX = 0;
	int minCellY = 0;
	int maxCellX = 4;
	int maxCellY = 4;

	Timer timer;
	bool isRunning = true;
	bool isLoop = false;

	AnimationComponent() = default;
	AnimationComponent(const AnimationComponent&) = default;
	AnimationComponent(const std::string& _name, int _eachClipLengthMS = 333, int _spriteWidth = 32, int _spriteHeight = 32,
		int _minCellX = 0, int _minCellY = 0, int _maxCellX = 4, int _maxCellY = 4, bool _isLoop = false) :
		name(_name), lengthMS(_eachClipLengthMS), spriteWidth(_spriteWidth), spriteHeight(_spriteHeight),
		minCellX(_minCellX), minCellY(_minCellY), maxCellX(_maxCellX), maxCellY(_maxCellY), isLoop(_isLoop) {}
};

struct AnimatorComponent {
	std::unordered_map<std::string, AnimationComponent> map;
	AnimationComponent* currentAnimation = nullptr;

	bool canSkipCurrentAnimation = true;
	float speedMultiplier = 1.0f;
};