#pragma once

class AnimationSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<AnimationComponent>());
        signature.set(Core::GetCoordinator().GetComponentType<SpriteComponent>());
        Core::GetCoordinator().SetSystemSignature<AnimationSystem>(signature);
    }

    void Update() {
        using namespace std::chrono;
        const auto now = steady_clock::now();
        static auto lastTime = now;
        const int frameDeltaMs = static_cast<int>(duration_cast<milliseconds>(now - lastTime).count());
        lastTime = now;

        for (auto const &entity: mEntities) {
            auto &animComponent = Core::GetCoordinator().GetComponent<AnimationComponent>(entity);
            auto &spriteComponent = Core::GetCoordinator().GetComponent<SpriteComponent>(entity);

            // Skip if the animation is not playing
            if (!animComponent.isPlaying)
                continue;

            if (animComponent.animationSpeed <= 0) {
                animComponent.animationSpeed = 1;
            }

            // Accumulate elapsed time once per frame (same delta for all entities).
            animComponent.elapsedTime += frameDeltaMs;

            // Check if it's time to update the animation frame
            while (animComponent.elapsedTime >= animComponent.animationSpeed) {
                animComponent.elapsedTime -= animComponent.animationSpeed;
                ++animComponent.currentFrame;

                // If we reached the end of the animation
                if (animComponent.currentFrame >= animComponent.frameCount) {
                    // If looping, go back to the first frame, otherwise stay on the last frame
                    animComponent.currentFrame = animComponent.loop ? 0 : animComponent.frameCount - 1;
                }

                // Update the source rectangle of the sprite to display the correct frame
                spriteComponent.srcRect.x = animComponent.currentFrame * animComponent.frameWidth;
                spriteComponent.srcRect.w = animComponent.frameWidth;
                spriteComponent.srcRect.h = animComponent.frameHeight;
            }
        }
    }
};
