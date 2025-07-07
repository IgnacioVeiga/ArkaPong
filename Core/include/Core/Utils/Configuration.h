#pragma once

#include <fstream>
#include "nlohmann-json/json.hpp"

using json = nlohmann::json;

inline json getDefaultConfig() {
    return {
        {
            "project", {
                {"name", "Untitled project"},
                {"version", "1.0.0"},
                {"company", "Unknown company"},
                {"description", ""},
                {"author", ""},
                {"license", ""}
            }
        },
        {
            "graphics", {
                {"logic_resolution", {{"width", 512}, {"height", 320}}},
                {
                    "resolutions", json::array({
                        {{"width", 800}, {"height", 600}},
                        {{"width", 1024}, {"height", 768}},
                        {{"width", 1280}, {"height", 720}},
                        {{"width", 1440}, {"height", 900}},
                        {{"width", 1920}, {"height", 1080}},
                        {{"width", 2560}, {"height", 1440}},
                        {{"width", 3840}, {"height", 2160}}
                    })
                },
                {"vsync", true},
                {"fullscreen", false},
                {"borderless", false}
            }
        },
        {
            "audio", {
                {"frequency", 44100},
                {"channels", 2},
                {"chunksize", 2048},
                {
                    "volume", {
                        {"master", 128},
                        {"music", 128},
                        {"sfx", 128}
                    }
                }
            }
        },
        {
            "physics", {
                {"collision_method", "spatial_hash"},
                {"gravity", 9.81}
            }
        }
    };
}

inline json readConfig() {
    if (std::ifstream file("config.json"); file.is_open()) {
        json config;
        file >> config;
        return config;
    }
    return getDefaultConfig();
}

inline void mergeConfig(json &base, const json &defaults) {
    for (auto it = defaults.begin(); it != defaults.end(); ++it) {
        if (base.find(it.key()) == base.end()) {
            base[it.key()] = it.value();
        } else if (base[it.key()].is_object()) {
            mergeConfig(base[it.key()], it.value());
        }
    }
}

inline void saveConfig(const json &config) {
    if (std::ofstream file("config.json"); file.is_open()) {
        file << config.dump(4);
    }
}
