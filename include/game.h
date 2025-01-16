#ifndef __GAME_H__
#define __GAME_H__

#include "engine.h"

#define CHUNK_WIDTH 10
#define CHUNK_HEIGHT 10

#define MAP_WIDTH 3 * CHUNK_WIDTH
#define MAP_HEIGHT 3 * CHUNK_HEIGHT

#define SQUARE_SIZE 40

#define WIN_W CHUNK_WIDTH * SQUARE_SIZE
#define WIN_H CHUNK_HEIGHT * SQUARE_SIZE

#define NUMBER_TILE_OFFSET 6

#define MINES CHUNK_WIDTH*CHUNK_HEIGHT*10/45

enum _state {
    HIDDEN = 0,
    REVEALED,
    FLAGGED
};

enum _textures {
    T_FLAG = 1,
    T_MINE,
    T_HIDDEN,
    T_WRONG,
    T_BADFLAG,
    T_BACKGROUND,
};

typedef struct _Game {
    Uint8 grid[MAP_HEIGHT][MAP_WIDTH]; // Minesweeper grid
    Uint8 state[MAP_HEIGHT][MAP_WIDTH]; // State of each tile (hidden, revealed, flagged)
    Uint32 score;
    bool start; // First click
    bool game_over; // Game over
    bool space_pressed; // Space pressed to move the grid
    int mx, my; // Mouse position
    int vx, vy; // Viewport position
    int chunkX, chunkY; // CENTER chunk coordinates
    int vchunkX, vchunkY; // Viewport chunk coordinates
} Game;

inline bool in_grid(int row, int col) {
    return row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH;
}

void init_game(Game *game);
void init_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]);
void load_chunks_to_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH], Uint8 chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH]);
void gen_numbers(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]);
void gen_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]);
void gen_mines(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]);

void create_tiles(Game *game);
void start_game(Game *game, int row, int col);
void reveal_tile(Game *game, int row, int col);
void reveal_bombs(Game *game, int row, int col);
void reveal_number(Game *game, int row, int col);

#endif // __GAME_H__