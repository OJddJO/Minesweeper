#ifndef __GAME_H__
#define __GAME_H__

#include "engine.h"

#define WIDTH 15
#define HEIGHT 20

#define SQUARE_SIZE 20
#define SQUARE_MARGIN 3

#define MINES 40

#define WIN_W WIDTH * SQUARE_SIZE
#define WIN_H HEIGHT * SQUARE_SIZE

enum _state {
    HIDDEN = 0,
    REVEALED,
    FLAGGED
};

enum _tiles {
    T_FLAG = 1,
    T_MINE,
    T_HIDDEN,
    T_HOVERED,
    T_REVEALED,
    T_WRONG,
    T_BACKGROUND,
};

typedef struct _Game {
    Uint8 grid[HEIGHT][WIDTH];
    Uint8 revealed[HEIGHT][WIDTH];
    Uint32 score;
    bool game_over;
} Game;

#endif