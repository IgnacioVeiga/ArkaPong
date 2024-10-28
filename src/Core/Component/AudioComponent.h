#pragma once

enum class AudioType
{
    SFX,
    BGM
};

struct AudioComponent
{
    std::string audioPath;
    AudioType type;
    bool isPlaying;
    bool loop;

    // Only for SFX
    int channel;
};
