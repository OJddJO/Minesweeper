#ifndef __GAME_H__
#define __GAME_H__

#include "SSGE.h"
#include <fileapi.h>
#include <dirent.h>

#define FPS 60

#define CHUNK_WIDTH 10
#define CHUNK_HEIGHT 10

#define MAP_WIDTH 3 * CHUNK_WIDTH
#define MAP_HEIGHT 3 * CHUNK_HEIGHT

#define SQUARE_SIZE 30

#define BORDER_SIZE 4.5

#define WIN_W (int)(CHUNK_WIDTH + BORDER_SIZE*2) * SQUARE_SIZE
#define WIN_H (int)(CHUNK_HEIGHT + BORDER_SIZE*2) * SQUARE_SIZE

#define NUMBER_TILE_OFFSET 6

#define MINES CHUNK_WIDTH*CHUNK_HEIGHT/5

#define SAVE_ANIM_FRAMES 100

#define MENU_ALPHA_STEP 10
#define MENU_FADE_MAX_ALPHA 200

enum _state {
    HIDDEN = 0,
    REVEALED,
    FLAGGED
};

enum _textures {
    T_HIDDEN = 1,
    T_MINE,
    T_FLAG,
    T_WRONG,
    T_BADFLAG,
    T_BACKGROUND,
};

typedef struct _Game {
    Uint8 grid[MAP_HEIGHT][MAP_WIDTH]; // Minesweeper grid
    Uint32 score;
    Uint32 frame_count;
    Uint32 save_frame; // Frame count when saved
    short menu_alpha; // Current alpha of the menu fade animation
    bool update_save_anim; // Update save animation
    bool update_menu_anim; // Update menu animation
    bool menu;
    bool game_over; // Game over
    bool space_pressed; // Space pressed to move the grid
    int mx, my; // Mouse position
    int vx, vy; // Viewport position (NW corner)
    int cx, cy; // Center chunk coordinates
} Game;

inline bool in_grid(int row, int col) {
    return row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH;
}

// Tile functions

void get_tile_info(Uint8 tile, Uint8 *value, Uint8 *state);
Uint8 get_tile_value(Uint8 tile);
Uint8 get_tile_state(Uint8 tile);
void store_tile_value(Uint8 *tile, Uint8 value);
void store_tile_state(Uint8 *tile, Uint8 state);

// Game init functions

void init_game(Game *game);
void init_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]);
void load_chunks_to_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH], Uint8 chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH]);
void gen_numbers(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]);
void gen_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]);
void gen_mines(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]);

void create_tiles(Game *game);
void start_game(Game *game, int row, int col);

// Game update functions

void reveal_tile(Game *game, int row, int col);
void reveal_bombs(Game *game, int row, int col);
void reveal_number(Game *game, int row, int col);

// Viewport/chunk functions

void calc_current_centered_chunk(Game *game, int *x, int *y);
void shift_game_chunks(Game *game, int dx, int dy);
void check_mine_valid(Game *game, Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col, int crow, int ccol);
void add_chunk_to_game(Game *game, int row, int col, int crow, int ccol);
void post_process_shift_chunks(Game *game, int dx, int dy);

// Save/load functions

void save_data(Game *game);
void load_data(Game *game);
void save_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col);
void save_chunks(Game *game);
void load_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col);
void load_chunks(Game *game, int row, int col);
void delete_save();

inline void save_game(Game *game) {
    save_data(game);
    save_chunks(game);
}

bool file_exists(const char *filename);

// Save animation functions

void check_upd_save_anim(Game *game);
void save_anim(Game *game);

// Menu functions

void check_upd_menu_fade(Game *game);
void menu_fade(Game *game);

inline void check_upd_anim(Game *game) {
    check_upd_save_anim(game);
    check_upd_menu_fade(game);
}

inline void anim(Game *game) {
    if (game->update_save_anim) save_anim(game);
    if (game->update_menu_anim) menu_fade(game);
    game->update_menu_anim = false;
    game->update_save_anim = false;
}

#endif // __GAME_H__