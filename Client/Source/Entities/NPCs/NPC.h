#pragma once
#include "../Entity.h"
#include "../../Components/TextRenderer.h"

class NPC: public Entity {
public:
	typedef NPC Super;
	TextRenderer nameTag;

	// Base Functions
	void Start() override;
	void Update() override;
	void Render() override;
	void OnKill() override;
	void OnDeath() override;

	virtual void OnPlayerNearby() {};
	virtual void OnPlayerAway() {};

	bool IsPlayerNearby() { return isPlayerNearby; }
	void SetNearbyThreshold(float value) { nearbyThreshold = value; }

	// Utility Functions
	std::string ToString() override {
		if (!this) return "This NPC has already been deleted. What are you doing?!";
		return "NPC " + name + " with GUID: " + std::to_string(guid);
	}

private:
	float nearbyThreshold = 60;
	bool isPlayerNearby = false;

protected:
	NPC() = delete;
	NPC(std::string name);
	NPC(std::string texturePath, std::string name);
	~NPC();
};