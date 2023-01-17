#include "NPC.h"

NPC::NPC(std::string name) : Entity(name) { Start(); }
NPC::NPC(std::string texturePath, std::string name) : Entity(texturePath, name) { Start(); }
NPC::~NPC() {}

// Base Functions
void NPC::Start() {
	transform.SetScale(4, 4);

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name, SDL_Color{ 0, 0, 0 });
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;
}
void NPC::Update() {}
void NPC::Render() {
	renderer.Render();
	nameTag.Render();
}
void NPC::OnKill() {}
void NPC::OnDeath() {}