#include "Block.h"

#include <intrin.h>

namespace BlockTools
{

    CompressedBlockVertex createCompressedBlockVertex(uint x, uint y, uint z, uint atlasIndex, uint normal)
    {
        CompressedBlockVertex info = 0;

        info |= normal << 24u;
        info |= atlasIndex << 16u;
        info |= z << 12u;
        info |= y << 4u;
        info |= x;

        //vec3 normalList[] = vec3[](vec3(1, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0), vec3(0, -1, 0), vec3(0, 0, 1), vec3(0, 0, -1));

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

    Block getBlock(BlockList* blockList, BlockList* lBlocks, BlockList* rBlocks, BlockList* fBlocks, BlockList* bBlocks, int x, int y, int z)
    {
        if (x < 0 && lBlocks != nullptr)
            return lBlocks->at(getLocalBlockIndex(CHUNK_WIDTH - 1, y, z));
        else if (x >= CHUNK_WIDTH && rBlocks != nullptr)
            return rBlocks->at(getLocalBlockIndex(0, y, z));

        if (z < 0 && bBlocks != nullptr)
            return bBlocks->at(getLocalBlockIndex(x, y, CHUNK_WIDTH - 1));
        else if (z >= CHUNK_WIDTH && fBlocks != nullptr)
            return fBlocks->at(getLocalBlockIndex(x, y, 0));

        if (x < 0 || x >= CHUNK_WIDTH || y < 0 || y >= WORLD_HEIGHT || z < 0 || z >= CHUNK_WIDTH)
            return { BLOCK_ID_AIR, 0 };

        return blockList->at(getLocalBlockIndex(x, y, z));
    }

}