#include "S_HandleLocalPlayerInput.h"
#include "Managers/InputManager.h"
#include "Managers/RenderManager.h"
#include "Managers/GameManager.h"
#include "Miscellaneous/Mouse.h"
#include "Miscellaneous/Utils.h"
#include "Game/Component/Components.h"

void S_HandleLocalPlayerInput::HandleMovement() {
    Core::Entity localPlayer = GAME.GetLocalPlayer();
    auto& transform = localPlayer.GetComponent<TransformComponent>();

    // Reset the velocity of the player.
    transform.velocity.x = 0;
    transform.velocity.y = 0;

    // Update velocity based on the held keys.
    if (InputMgr.IsKeyHeld(SDLK_w) || InputMgr.IsKeyHeld(SDLK_UP))
        transform.velocity.y += -1;
    if (InputMgr.IsKeyHeld(SDLK_s) || InputMgr.IsKeyHeld(SDLK_DOWN))
        transform.velocity.y += 1;
    if (InputMgr.IsKeyHeld(SDLK_a) || InputMgr.IsKeyHeld(SDLK_LEFT))
        transform.velocity.x += -1;
    if (InputMgr.IsKeyHeld(SDLK_d) || InputMgr.IsKeyHeld(SDLK_RIGHT))
        transform.velocity.x += 1;

    // Update the Animator current Animation.
    {
        auto& animator = localPlayer.GetComponent<AnimatorComponent>();
        if (transform.velocity.Magnitude() > 0.001f)
            animator.currentAnimation = &animator.map["Move"];
        else
            animator.currentAnimation = &animator.map["Idle"];
    }
    
    // Handle Image Flip based on mouse position.
    {
        auto& renderer = localPlayer.GetComponent<SpriteRendererComponent>();
        Vector2 mousePos = Mouse::GetPosition();
        renderer.isFlipped = mousePos.x > MainRenderer.SCREEN_WIDTH / 2;
    }
}

void S_HandleLocalPlayerInput::HandleAbilities() {
    Core::Entity localPlayer = GAME.GetLocalPlayer();
    auto& abilitySystem = localPlayer.GetComponent<AbilitySystemComponent>();
    
}

void S_HandleLocalPlayerInput::HandleDebug() {
    auto curSceneName = Core::SceneMgr.GetCurrentScene()->name;
    if (InputMgr.IsKeyPressed(SDLK_g)) {
        if (curSceneName == "Town")
            Core::SceneMgr.ChangeScene("DefiledCathedral");
        else
            Core::SceneMgr.ChangeScene("Town");
    }
}

void S_HandleLocalPlayerInput::Start() {}
void S_HandleLocalPlayerInput::Update() {
    HandleMovement();
    HandleAbilities();

#if _DEBUG
    HandleDebug();
#endif
}

void S_HandleLocalPlayerInput::LateUpdate() {}
void S_HandleLocalPlayerInput::Destroy() {}