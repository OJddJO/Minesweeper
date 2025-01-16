#include "game.h"

/**
 * Initializes the game structure
 * \param game The game to initialize
 */
void init_game(Game *game) {
    init_grid(game->state);
    game->score = 0;
    game->start = true;
    game->game_over = false;
    game->space_pressed = false;
    game->mx = 0;
    game->my = 0;
    game->vx = -CHUNK_HEIGHT * SQUARE_SIZE;
    game->vy = -CHUNK_WIDTH * SQUARE_SIZE;
    game->chunkX = 0;
    game->chunkY = 0;
    game->vchunkX = 0;
    game->vchunkY = 0;

    destroy_all_objects();
    create_tiles(game);
}

/**
 * Initializes the grid with 0s
 * \param grid The grid to initialize
 */
void init_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            grid[row][col] = 0;
        }
    }
}

/**
 * Loads the chunks to the grid
 * \param grid The grid to load the chunks to
 * \param chunks The chunks to load
 */
void load_chunks_to_grid(Uint8 grid[MAP_HEIGHT][MAP_WIDTH], Uint8 chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int row = 0; row < CHUNK_HEIGHT; row++) {
                for (int col = 0; col < CHUNK_WIDTH; col++) {
                    grid[i*CHUNK_HEIGHT + row][j*CHUNK_WIDTH + col] = chunks[i][j][row][col];
                }
            }
        }
    }
}

/**
 * Generates the numbers in the grid
 * \param grid The grid to generate the numbers in
 */
void gen_numbers(Uint8 grid[MAP_HEIGHT][MAP_WIDTH]) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            if (grid[row][col] == 9) {
                continue;
            }

            int count = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (!in_grid(row+i, col+j)) {
                        continue;
                    }
                    if (grid[row+i][col+j] == 9) {
                        count++;
                    }
                }
            }
            grid[row][col] = count;
        }
    }
}

/**
 * Generates a chunk
 * \param chunk The chunk to generate
 */
void gen_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]) {
    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            chunk[row][col] = 0;
        }
    }
    gen_mines(chunk);
}

/**
 * Generates the mines in a chunk
 * \param chunk The chunk to generate the mines in
 */
void gen_mines(Uint8 grid[CHUNK_HEIGHT][CHUNK_WIDTH]) {
    for (int i = 0; i < MINES; i++) {
        int row = rand() % CHUNK_HEIGHT;
        int col = rand() % CHUNK_WIDTH;
        if (grid[row][col] == 9) {
            i--;
        } else {
            grid[row][col] = 9;
        }
    }
}

/**
 * Creates the tiles for the full grid
 */
void create_tiles(Game *game) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            char name[20];
            sprintf(name, "%d_%d", row, col);
            Texture *texture;
            switch (game->state[row][col])  {
                case HIDDEN:
                    texture = get_texture(T_HIDDEN);
                    break;
                case FLAGGED:
                    texture = get_texture(T_FLAG);
                    break;
                case REVEALED:
                    if (game->grid[row][col] == 9) {
                        texture = get_texture(T_WRONG);
                    } else {
                        texture = get_texture(game->grid[row][col] + NUMBER_TILE_OFFSET);
                    }
                    break;
            }
            create_object(name, texture, (col - CHUNK_WIDTH) * SQUARE_SIZE, (row - CHUNK_HEIGHT) * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, false, NULL);
        }
    }
}

/**
 * Starts the game
 * \param game The game to start
 */
void start_game(Game *game, int row, int col) {
    init_grid(game->grid);
    
    Uint8 chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gen_chunk(chunks[i][j]);
        }
    }
    load_chunks_to_grid(game->grid, chunks);
    gen_numbers(game->grid);

    while (game->grid[row][col] != 0) {
        gen_chunk(chunks[1][1]);
        load_chunks_to_grid(game->grid, chunks);
        gen_numbers(game->grid);
    }

    // for (int row = 0; row < MAP_HEIGHT; row++) {
    //     for (int col = 0; col < MAP_WIDTH; col++) {
    //         printf("%d ", game->grid[row][col]);
    //     }
    //     printf("\n");
    // }

    game->start = false;
}

/**
 * Reveals a tile
 * \param game The game to reveal the tile in
 * \param row The row of the tile to reveal
 * \param col The column of the tile to reveal
 */
void reveal_tile(Game *game, int row, int col) {
    game->state[row][col] = REVEALED;
    char name[6];
    sprintf(name, "%d_%d", row, col);
    Object *obj = get_object_by_name(name);
    if (game->grid[row][col] == 9) {
        change_object_texture(obj, get_texture(T_WRONG));
        reveal_bombs(game, row, col);
        game->game_over = true;
    } else {
        game->score++;
        change_object_texture(obj, get_texture(game->grid[row][col] + NUMBER_TILE_OFFSET));
        if (game->grid[row][col] == 0) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (!in_grid(row+i, col+j)) {
                        continue;
                    }
                    if (game->state[row+i][col+j] == HIDDEN) {
                        reveal_tile(game, row+i, col+j);
                    }
                }
            }
        }
    }
}

/**
 * Reveals all bombs
 * \param game The game to reveal the bombs in
 */
void reveal_bombs(Game *game, int row, int col) {
    for (int row_ = 0; row_ < MAP_HEIGHT; row_++) {
        for (int col_ = 0; col_ < MAP_WIDTH; col_++) {
            char name[6];
            sprintf(name, "%d_%d", row_, col_);
            Object *obj = get_object_by_name(name);
            if ((row_ == row && col_ == col) || game->state[row_][col_] == REVEALED) {
                continue;
            }
            if (game->state[row_][col_] == FLAGGED && game->grid[row_][col_] == 9) {
                continue;
            } else if (game->state[row_][col_] == FLAGGED && game->grid[row_][col_] != 9) {
                change_object_texture(obj, get_texture(T_BADFLAG));
            } else if (game->grid[row_][col_] == 9) {
                change_object_texture(obj, get_texture(T_MINE));
            }
        }
    }
}

/**
 * Reveals around the number tile if all flags are placed
 * \param game The game to reveal the number in
 * \param row The row of the number tile
 * \param col The column of the number tile
 */
void reveal_number(Game *game, int row, int col) {
    int n = game->grid[row][col];
    int flag_count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!in_grid(row+i, col+j)) {
                continue;
            }
            if (game->state[row+i][col+j] == FLAGGED) {
                flag_count++;
            }
        }
    }
    if (flag_count != n) {
        return;
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!in_grid(row+i, col+j)) {
                continue;
            }
            if (game->state[row+i][col+j] == HIDDEN) {
                reveal_tile(game, row+i, col+j);
            }
        }
    }
}
