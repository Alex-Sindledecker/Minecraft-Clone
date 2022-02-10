#include "TerrainGenerator.h"

#include "../Utils/Defs.h"

namespace Terrain
{
    static int mSeed;
    static siv::PerlinNoise noise;

    void setSeed(unsigned int seed)
    {
        mSeed = seed;
        noise.reseed(mSeed);
    }

    Block getBlock(uint x, uint y, uint z)
    {
        double noiseValue = (noise.noise2D(x, z) + 1.0) / 2.0;
        int maxHeight = (int)(noiseValue * WORLD_HEIGHT / 10);

        if (y > maxHeight || y < 0)
            return { BLOCK_ID_AIR, 0 };
        if (y == maxHeight)
            return { BLOCK_ID_GRASS, 0 };
        else if (y > maxHeight - 5)
            return { BLOCK_ID_DIRT, 0 };
        return { BLOCK_ID_STONE, 0 };
    }

}