#include "Beam.h"

// Constructor & Deconstructor
Beam::Beam(): Entity("Assets/VFX/Thunderstrike wo blur.png", "UnnamedExplosion") { Start(); }
Beam::~Beam() {
	CAnimator->Delete();
	CAnimator = nullptr;
}

// Base Functions
void Beam::Start() {
	// Set Scale to a bit bigger.
	transform.SetScale(1.0f, 3.0f);

	// Set offset so it looks cooler :^)
	renderer.SetOffset(0, -((int)renderer.GetHeight()*1.75f));

	// Animator Component
	CAnimator = AddComponent<Animator>();
	CAnimator->Add(Animation("Idle", 60, 64, 64, 0, 0, 13, 0, true));
}

void Beam::Update() { Entity::Update(); CAnimator->Update(); }
void Beam::Render() { renderer.Render(); }