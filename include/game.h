#ifndef __GAME_H__
#define __GAME_H__

#include "engine.h"

#define WIDTH 20
#define HEIGHT 25

#define SQUARE_SIZE 30

#define WIN_W WIDTH * SQUARE_SIZE
#define WIN_H HEIGHT * SQUARE_SIZE

#define NUMBER_TILE_OFFSET 8

#define MINES WIDTH*HEIGHT/5

enum _state {
    HIDDEN = 0,
    REVEALED,
    FLAGGED
};

typedef struct _Game {
    Uint8 grid[HEIGHT][WIDTH];
    Uint8 state[HEIGHT][WIDTH];
    Uint32 score;
    bool start;
    bool game_over;
    int mx, my; // Mouse position for dragging
    bool space_pressed;
} Game;

#endif