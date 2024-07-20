#pragma once

#include "../Coordinator.h"
#include "../Component/AudioComponent.h"

extern Coordinator gCoordinator;

class AudioSystem : public System
{
public:
    void Init() {}

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &audioComponent = gCoordinator.GetComponent<AudioComponent>(entity);

            if (audioComponent.isPlaying)
            {
                if (audioComponent.chunk)
                {
                    Mix_PlayChannel(-1, audioComponent.chunk, audioComponent.loop ? -1 : 0);
                }
                else if (audioComponent.music)
                {
                    Mix_PlayMusic(audioComponent.music, audioComponent.loop ? -1 : 1);
                }

                // Reset after playing
                audioComponent.isPlaying = false;
            }
        }
    }
};
