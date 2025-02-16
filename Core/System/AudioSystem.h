#pragma once

#include <SDL_mixer.h>
#include "../Manager/AudioManager.h"

class AudioSystem : public System
{
public:
    void Init()
    {
        Signature signature{};
        signature.set(Core::coordinator.GetComponentType<AudioComponent>());
        Core::coordinator.SetSystemSignature<AudioSystem>(signature);
    }

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &audioComponent = Core::coordinator.GetComponent<AudioComponent>(entity);

            if (!audioComponent.isPlaying)
                continue;

            if (audioComponent.type == AudioType::SFX && (audioComponent.channel == -1 || !Mix_Playing(audioComponent.channel)))
            {
                Mix_Chunk *chunk = AudioManager::LoadChunk(audioComponent.audioPath);
                audioComponent.channel = Mix_PlayChannel(-1, chunk, audioComponent.loop ? -1 : 0);
            }
            else if (audioComponent.type == AudioType::BGM && !Mix_PlayingMusic())
            {
                Mix_Music *music = AudioManager::LoadMusic(audioComponent.audioPath);
                Mix_PlayMusic(music, audioComponent.loop ? -1 : 1);
            }

            // Reset after playing
            audioComponent.isPlaying = false;
        }
    }
};
