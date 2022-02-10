#pragma once

typedef unsigned int uint;

constexpr int CHUNK_WIDTH = 15;
constexpr int WORLD_HEIGHT = 255;
constexpr int CHUNK_RENDER_DISTANCE = 15;

constexpr uint ATLAS_SIZE = 256;
constexpr uint ATLAS_IMAGE_SIZE = 16;

constexpr uint NORMAL_SHIFT = 24u;
constexpr uint NORMAL_RIGHT = 0u << NORMAL_SHIFT;
constexpr uint NORMAL_LEFT = 1u << NORMAL_SHIFT;
constexpr uint NORMAL_UP = 2u << NORMAL_SHIFT;
constexpr uint NORMAL_DOWN = 3u << NORMAL_SHIFT;
constexpr uint NORMAL_FRONT = 4u << NORMAL_SHIFT;
constexpr uint NORMAL_BACK = 5u << NORMAL_SHIFT;

constexpr uint8_t BLOCK_ID_AIR = 0;
constexpr uint8_t BLOCK_ID_GRASS = 1;
constexpr uint8_t BLOCK_ID_DIRT = 2;
constexpr uint8_t BLOCK_ID_STONE = 3;

constexpr uint8_t LEFT_BLOCK = 0;
constexpr uint8_t RIGHT_BLOCK = 1;
constexpr uint8_t BACK_BLOCK = 2;
constexpr uint8_t FRONT_BLOCK = 3;

//Defined in Application.cpp
extern const int DEFAULT_WINDOW_WIDTH;
extern const int DEFAULT_WINDOW_HEIGHT;