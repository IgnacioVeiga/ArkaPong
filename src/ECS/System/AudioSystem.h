#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/AudioComponent.h"
#include "../../Utils/AudioManager.h"

class AudioSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<AudioComponent>());
        Game::coordinator.SetSystemSignature<AudioSystem>(signature);
    }

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &audioComponent = Game::coordinator.GetComponent<AudioComponent>(entity);

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
