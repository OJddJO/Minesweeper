#ifndef __GAME_H__
#define __GAME_H__

#include "engine.h"

#define WIDTH 20
#define HEIGHT 25

#define SQUARE_SIZE 30

#define WIN_W WIDTH * SQUARE_SIZE
#define WIN_H HEIGHT * SQUARE_SIZE

#define NUMBER_TILE_OFFSET 6

#define MINES WIDTH*HEIGHT/5

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
    Uint8 grid[HEIGHT][WIDTH];
    Uint8 state[HEIGHT][WIDTH];
    Uint32 score;
    bool start;
    bool game_over;
    bool space_pressed;
    int mx, my; // Mouse position
    int vx, vy; // Viewport position
} Game;

#endif