#include "Core/Utils/Window.h"
#include "Core/Utils/CoreConstants.h"
#include "Core/Manager/AudioManager.h"
#include "Core/Manager/FontManager.h"
#include "Core/Manager/TextureManager.h"

#include <SDL2/SDL.h>
#include <algorithm>

#if defined(_MSC_VER)
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <iostream>

namespace
{
    int ReadPositiveInt(const json& source, const char* key, const int fallback)
    {
        const int value = source.value(key, fallback);
        return value > 0 ? value : fallback;
    }

    Resolution ReadResolution(const json& source, const Resolution fallback)
    {
        if (!source.is_object()) {
            return fallback;
        }

        return {
            ReadPositiveInt(source, "width", fallback.width),
            ReadPositiveInt(source, "height", fallback.height)
        };
    }

    int ClampMixerVolume(const int value)
    {
        return std::clamp(value, 0, MIX_MAX_VOLUME);
    }
}

Window::Window()
    : logicalWidth(SCREEN_WIDTH), logicalHeight(SCREEN_HEIGHT),
      windowWidth(SCREEN_WIDTH), windowHeight(SCREEN_HEIGHT),
      window(nullptr), renderer(nullptr),
      availableResolutions{
          {SCREEN_WIDTH, SCREEN_HEIGHT},
          {1280, 720},
          {1920, 1080},
          {2560, 1440},
          {3840, 2160}
      }
{
}

Window::~Window() {
    CleanUp();
}

bool Window::Init(const char* title, const json& config) {
    // Keep the runtime config parsing in one place so the portable engine and the
    // example game agree on the same logical resolution, window size and audio setup.
    const json graphicsConfig = config.value("graphics", json::object());
    const json audioConfig = config.value("audio", json::object());

    const Resolution fallbackLogicalResolution{SCREEN_WIDTH, SCREEN_HEIGHT};
    const Resolution logicalResolution = ReadResolution(
        graphicsConfig.value("logic_resolution", json::object()),
        fallbackLogicalResolution);
    logicalWidth = logicalResolution.width;
    logicalHeight = logicalResolution.height;

    availableResolutions.clear();
    if (graphicsConfig.contains("resolutions") && graphicsConfig["resolutions"].is_array()) {
        for (const auto& resolutionConfig : graphicsConfig["resolutions"]) {
            availableResolutions.push_back(ReadResolution(resolutionConfig, logicalResolution));
        }
    }
    if (availableResolutions.empty()) {
        availableResolutions = {
            logicalResolution,
            {1280, 720},
            {1920, 1080},
            {2560, 1440},
            {3840, 2160}
        };
    }

    windowWidth = availableResolutions.front().width;
    windowHeight = availableResolutions.front().height;
    const bool vsyncEnabled = graphicsConfig.value("vsync", true);
    const bool fullscreenEnabled = graphicsConfig.value("fullscreen", false);
    const bool borderlessEnabled = graphicsConfig.value("borderless", false);

    const int audioFrequency = ReadPositiveInt(audioConfig, "frequency", AUDIO_FREQUENCY);
    const int audioChannels = ReadPositiveInt(audioConfig, "channels", 2);
    const int audioChunkSize = ReadPositiveInt(audioConfig, "chunksize", 2048);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        CleanUp();
        return false;
    }

    if (Mix_OpenAudio(audioFrequency, MIX_DEFAULT_FORMAT, audioChannels, audioChunkSize) == -1) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        CleanUp();
        return false;
    }

    Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (borderlessEnabled) {
        windowFlags |= SDL_WINDOW_BORDERLESS;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, windowFlags);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        CleanUp();
        return false;
    }

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if (vsyncEnabled) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        CleanUp();
        return false;
    }

    SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

    const json volumeConfig = audioConfig.value("volume", json::object());
    const int masterVolume = ClampMixerVolume(volumeConfig.value("master", MIX_MAX_VOLUME));
    const int musicVolume = ClampMixerVolume(volumeConfig.value("music", MIX_MAX_VOLUME));
    const int sfxVolume = ClampMixerVolume(volumeConfig.value("sfx", MIX_MAX_VOLUME));
    Mix_VolumeMusic((musicVolume * masterVolume) / MIX_MAX_VOLUME);
    Mix_Volume(-1, (sfxVolume * masterVolume) / MIX_MAX_VOLUME);

    if (fullscreenEnabled) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    return true;
}

void Window::CleanUp() {
    // Destroy engine-managed resources first while the renderer/audio subsystems are alive.
    TextureManager::Clear();
    FontManager::Cleanup();
    AudioManager::Cleanup();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    int frequency = 0;
    int channels = 0;
    Uint16 format = 0;
    if (Mix_QuerySpec(&frequency, &format, &channels) != 0) {
        Mix_CloseAudio();
    }

    if (TTF_WasInit() != 0) {
        TTF_Quit();
    }

    if (SDL_WasInit(0) != 0) {
        SDL_Quit();
    }
}

// TODO: fix fullscreen mode in Linux, not working on KDE
void Window::SetWindowMode(const int resolutionIndex, const Uint32 flags) {
    if (!window || !renderer) {
        std::cerr << "Window/renderer not initialized" << std::endl;
        return;
    }

    if (resolutionIndex < 0 || resolutionIndex >= static_cast<int>(availableResolutions.size())) {
        std::cerr << "Invalid resolution index" << std::endl;
        return;
    }

    const auto& res = availableResolutions[resolutionIndex];
    windowWidth = res.width;
    windowHeight = res.height;

    SDL_SetWindowSize(window, res.width, res.height);
    SDL_SetWindowFullscreen(window, flags);
    SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

    //#ifdef __linux__
    //  SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    //#endif
}
