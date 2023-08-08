#pragma once
#include "../Entity.h"
#include "../../Miscellaneous/Timer.h"
#include "../../Components/Animator.h"

class Explosion: public Entity {
public:
	// Components
	Animator* CAnimator;
	Timer timer{};

	// Life Time of this entity in milliseconds
	float lifeTime = 1000;

	// Constructor & Deconstructor
	Explosion(float _lifeTime = 1000);
	~Explosion();

	// Base Functions
	void Start() override;
	void Update() override;
	void Render() override;

	// Events
	void OnKill() {}
	void OnDeath() {}
};