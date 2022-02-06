#pragma once

#include "Block.h"
#include "../PerlinNoise.hpp"
#include "../Utils/Defs.h"

namespace Terrain
{
	void setSeed(unsigned int seed);
	Block getBlock(uint x, uint y, uint z);
}