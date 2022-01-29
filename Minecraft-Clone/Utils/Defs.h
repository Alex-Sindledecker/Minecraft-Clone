#pragma once

constexpr int CHUNK_WIDTH = 15;
constexpr int WORLD_HEIGHT = 255;
constexpr int CHUNK_RENDER_DISTANCE = 15;

constexpr unsigned int ATLAS_SIZE = 256;
constexpr unsigned int ATLAS_IMAGE_SIZE = 16;

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