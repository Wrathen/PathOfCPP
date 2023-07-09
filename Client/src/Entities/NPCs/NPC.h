#pragma once
#include "../Entity.h"
#include "../../Components/TextRenderer.h"

class NPC : public Entity {
public:
    typedef NPC Super;
    TextRenderer nameTag;
    bool isPlayerNearby = false;

    // Base Functions
    void Start() override;
    void Update() override;
    void Render() override;
    void OnKill() override;
    void OnDeath() override;

    virtual void OnPlayerNearby() {};
    virtual void OnPlayerAway() {};

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This NPC has already been deleted. What are you doing?!";
        return "NPC " + name + " with GUID: " + std::to_string(guid);
    }

protected:
    NPC() = delete;
    NPC(std::string name);
    NPC(std::string texturePath, std::string name);
    ~NPC();
};