#include "Block.h"

#include <intrin.h>

namespace BlockTools
{


    CompressedBlockVertex createCompressedBlockVertex(unsigned int x, unsigned int y, unsigned int z, unsigned int atlasIndex, unsigned int imageCorner)
    {
        CompressedBlockVertex info = 0;

        info |= imageCorner << 24u;
        info |= atlasIndex << 16u;
        info |= z << 12u;
        info |= y << 4u;
        info |= x;

        /*
        * Decompresion
        x = vertex & 0xFu;
        y = (vertex & 0xFF0u) >> 4u;
        z = (vertex & 0xF000u) >> 12u;
        atlasIndex = (vertex & 0xFF0000u) >> 16u;
        imageCorner = (vertex & 0x3000000u) >> 24u;
        */

        return info;
    }

    int getLocalBlockIndex(uint8_t x, uint8_t y, uint8_t z)
    {
        return CHUNK_WIDTH * CHUNK_WIDTH * y + (CHUNK_WIDTH * z + x);
    }

    uint8_t getBlockAtlasIndex(Block& block)
    {
        return block.id - 1;
    }

}