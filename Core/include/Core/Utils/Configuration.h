#pragma once

#include "nlohmann-json/json.hpp"

using json = nlohmann::json;

json getDefaultConfig();
void mergeConfig(json& base, const json& defaults);
json readConfig(const std::string& path = "config.json");
void saveConfig(const json& config);
