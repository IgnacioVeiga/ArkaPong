#pragma once

#include "ParallaxLayer.h"
#include <vector>

struct ParallaxBackgroundComponent {
	std::vector<ParallaxLayer> layers;
};
