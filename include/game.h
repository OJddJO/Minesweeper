#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fileapi.h>
#include <dirent.h>

#include "SSGE/SSGE.h"

#define FPS 60

#define CHUNK_WIDTH 10
#define CHUNK_HEIGHT 10

#define MAP_WIDTH 3
#define MAP_HEIGHT 3

#define TILE_SIZE 30

#define BORDER_SIZE 4.5

#define WIN_W (int8_t)(CHUNK_WIDTH + BORDER_SIZE*2) * TILE_SIZE
#define WIN_H (int8_t)(CHUNK_HEIGHT + BORDER_SIZE*2) * TILE_SIZE

#define NUMBER_TILE_OFFSET 5

#define MINES CHUNK_WIDTH*CHUNK_HEIGHT/5

enum _state {
    S_HIDDEN = 0,
    S_REVEALED,
    S_FLAGGED
};

enum _textures {
    T_HIDDEN = 0,
    T_MINE,
    T_FLAG,
    T_WRONG,
    T_BADFLAG,
    T_BACKGROUND,
};

typedef uint8_t Chunk[CHUNK_HEIGHT][CHUNK_WIDTH];
typedef Chunk Map[MAP_HEIGHT][MAP_WIDTH];

typedef struct _Game {
    uint32_t    ids[CHUNK_HEIGHT * MAP_HEIGHT][CHUNK_WIDTH * MAP_WIDTH];
    Map         map;
} Game;

/**
 * Convert chunk coordinates to linear coordinates
 * \param crow The row of the chunk
 * \param ccol The col of the chunk
 * \param row The row of the tile in the chunk
 * \param col The col of the tile in the chunk
 * \param lrow The buffer to store the linear row
 * \param lcol The buffer to store the linear col
 */
inline void chunkToLinear(int8_t crow, int8_t ccol, int8_t row, int8_t col, int64_t *lrow, int64_t *lcol) {
    *lrow = crow * CHUNK_HEIGHT + row;
    *lcol = ccol * CHUNK_WIDTH + col;
}

/**
 * Convert linear to chunk coordinates
 * \param lrow The row of the tile
 * \param lcol The col of the tile
 * \param crow The buffer to store the row of the chunk
 * \param ccol The buffer to store the col of the chunk
 * \param row The buffer to store the row of the tile in the chunk
 * \param col The buffer to store the col of the tile in the chunk
 */
inline void linearToChunk(int64_t lrow, int64_t lcol, int8_t *crow, int8_t *ccol, int8_t *row, int8_t *col) {
    *crow = lrow / CHUNK_HEIGHT;
    *ccol = lcol / CHUNK_WIDTH;
    *row = lrow % CHUNK_HEIGHT;
    *col = lcol % CHUNK_WIDTH;
}

inline bool outOfMap(int8_t crow, int8_t ccol, int8_t row, int8_t col) {
    int64_t lrow = 0, lcol = 0;
    chunkToLinear(crow, ccol, row, col, &lrow, &lcol);
    return (
        lrow < 0 || lrow >= MAP_HEIGHT * CHUNK_HEIGHT ||
        lcol < 0 || lcol >= MAP_WIDTH * CHUNK_WIDTH
    );
}

/**
 * Gets the value and state of a tile
 * \param tile The tile to get the info from
 * \param value The variable to store the value in
 * \param state The variable to store the state in
 */
inline void getTileInfo(uint8_t tile, uint8_t *value, uint8_t *state) {
    *value = (uint8_t)(tile & 0b00001111);
    *state = (uint8_t)((tile & 0b11000000) >> 6);
}

/**
 * Gets the value of a tile
 * \param tile The tile to get the value from
 */
inline uint8_t getTileValue(uint8_t tile) {
    return (uint8_t)(tile & 0b00001111);
}

/**
 * Gets the state of a tile
 * \param tile The tile to get the state from
 */
inline uint8_t getTileState(uint8_t tile) {
    return (uint8_t)((tile & 0b11000000) >> 6);
}

/**
 * Stores a value in a tile
 * \param tile The tile to store the value in
 * \param value The value to store
 */
inline void storeTileValue(uint8_t *tile, uint8_t value) {
    *tile = (uint8_t)((*tile & 0b11000000) | value);
}

/**
 * Stores a state in a tile
 * \param tile The tile to store the state in
 * \param state The state to store
 */
inline void storeTileState(uint8_t *tile, uint8_t state) {
    *tile = (uint8_t)((*tile & 0b00001111) | (state << 6));
}

void printChunk(Chunk chunk);
void printMap(Map map);

void genChunk(Chunk chunk);
void initGame(Game *game);

#endif // __GAME_H__