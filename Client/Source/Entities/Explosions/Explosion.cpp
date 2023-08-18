#include "Explosion.h"

// Constructor & Deconstructor
Explosion::Explosion(float _lifeTime): lifeTime(_lifeTime), Entity("Assets/VFX/Explosion.png", "UnnamedExplosion") { Start(); }
Explosion::~Explosion() {
	CAnimator->Delete();
	CAnimator = nullptr;
}

// Base Functions
void Explosion::Start() {
	// Reset timer
	timer.Reset();

	// Set render scale.
	transform.SetScale(5.0f, 5.0f);
	
	// Animator Component
	CAnimator = AddComponent<Animator>();
	CAnimator->Add(Animation("Idle", 150, 46, 46, 0, 0, 7, 0, true));
	lifeTime = CAnimator->GetFullCycleLengthInMilliseconds();
}
void Explosion::Update() {
	// Update Animator
	CAnimator->Update();

	// If we have lived for enough time, it's time to pass into the Valhalla.
	if (timer.GetTimeMS() > lifeTime)
		Delete();
}
void Explosion::Render() { renderer.Render(); }