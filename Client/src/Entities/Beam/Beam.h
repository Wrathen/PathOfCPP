#pragma once
#include "../Entity.h"
#include "../../Components/Animator.h"

class Beam: public Entity {
public:
	// Components
	Animator* CAnimator;

	// Constructor & Deconstructor
	Beam();
	~Beam();

	// Base Functions
	void Start() override;
	void Update() override;
	void Render() override;

	// Events
	void OnKill() {}
	void OnDeath() {}
};