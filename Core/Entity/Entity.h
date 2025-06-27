#pragma once

#include <bitset>
#include <cstdint>

// A simple type alias
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

// Used to define the size of arrays later on
constexpr Entity MAX_ENTITIES = 5000;
constexpr ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
