#include "S_UpdateAnimators.h"
#include "Miscellaneous/Utils.h"
#include "Game/Component/Components.h"

void S_UpdateAnimators::Start() {}
void S_UpdateAnimators::Update() {
	auto& reg = Utils::GetRegistry();
	auto group = reg.group<AnimatorComponent>(entt::get<SpriteRendererComponent>);

    // Update each animator's current animation.
    group.each([](auto entity, auto& animator, auto& renderer){
        auto& anim = animator.currentAnimation;

        // If the anim variable is faulty or the animation is not running, return.
        if (!anim || !anim->isRunning)
            return;

        // If we are not ready for the next tick interval, we shouldn't continue until we are ready.
        if (anim->timer.GetTimeMS() < (anim->lengthMS / animator.speedMultiplier))
            return;

        // Update the current offsets (x, y).
        if (++anim->currentX > anim->maxCellX) {
            if (++anim->currentY > anim->maxCellY) {
                // if (!anim->isLoop) OnAnimationEnded();
                anim->isRunning = anim->isLoop;
                anim->currentY = anim->minCellY;
            }

            anim->currentX = anim->minCellX;
        }

        // Set the renderer positions accordingly.
        renderer.width = anim->spriteWidth;
        renderer.height = anim->spriteHeight;
        renderer.sourceOffset.x = anim->currentX * anim->spriteWidth;
        renderer.sourceOffset.y = anim->currentY * anim->spriteHeight;

        // Reset the Animation Timer for the next tick interval.
        anim->timer.Reset();
    });
}

void S_UpdateAnimators::LateUpdate() {}
void S_UpdateAnimators::Destroy() {}