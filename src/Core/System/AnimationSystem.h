#pragma once

class AnimationSystem : public System
{
public:
    void Init()
    {
        Signature signature{};
        signature.set(Game::coordinator.GetComponentType<AnimationComponent>());
        signature.set(Game::coordinator.GetComponentType<SpriteComponent>());
        Game::coordinator.SetSystemSignature<AnimationSystem>(signature);
    }

    void Update()
    {
        using namespace std::chrono;
        // Get the current time
        auto now = steady_clock::now();
        // Store the last time we updated the animations
        static auto lastTime = now;

        for (auto const &entity : mEntities)
        {
            // Get the animation and sprite components of the entity
            auto &animComponent = Game::coordinator.GetComponent<AnimationComponent>(entity);
            auto &spriteComponent = Game::coordinator.GetComponent<SpriteComponent>(entity);

            // Skip if the animation is not playing
            if (!animComponent.isPlaying)
                continue;

            // Calculate the elapsed time since the last update
            animComponent.elapsedTime += duration_cast<milliseconds>(now - lastTime).count();
            // Update the lastTime to now
            lastTime = now;

            // Check if it's time to update the animation frame
            if (animComponent.elapsedTime >= animComponent.animationSpeed)
            {
                // Reset elapsed time
                animComponent.elapsedTime = 0;
                // Move to the next frame
                animComponent.currentFrame++;

                // If we reached the end of the animation
                if (animComponent.currentFrame >= animComponent.frameCount)
                {
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
