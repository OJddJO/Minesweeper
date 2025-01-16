#include "game.h"

/**
 * Gets the value and state of a tile
 * \param tile The tile to get the info from
 * \param value The variable to store the value in
 * \param state The variable to store the state in
 */
void get_tile_info(Uint8 tile, Uint8 *value, Uint8 *state) {
    *value = (Uint8)(tile & 0b00001111);
    *state = (Uint8)((tile & 0b11000000) >> 6);
}

/**
 * Gets the value of a tile
 * \param tile The tile to get the value from
 */
Uint8 get_tile_value(Uint8 tile) {
    return (Uint8)(tile & 0b00001111);
}

/**
 * Gets the state of a tile
 * \param tile The tile to get the state from
 */
Uint8 get_tile_state(Uint8 tile) {
    return (Uint8)((tile & 0b11000000) >> 6);
}

/**
 * Stores a value in a tile
 * \param tile The tile to store the value in
 * \param value The value to store
 */
void store_tile_value(Uint8 *tile, Uint8 value) {
    *tile = (Uint8)((*tile & 0b11000000) | value);
}

/**
 * Stores a state in a tile
 * \param tile The tile to store the state in
 * \param state The state to store
 */
void store_tile_state(Uint8 *tile, Uint8 state) {
    *tile = (Uint8)((*tile & 0b00001111) | (state << 6));
}

/**
 * Initializes the game structure
 * \param game The game to initialize
 */
void init_game(Game *game) {
    init_grid(game->grid);
    game->score = 0;
    game->game_over = false;
    game->space_pressed = false;
    game->mx = 0;
    game->my = 0;
    game->vx = -CHUNK_HEIGHT * SQUARE_SIZE;
    game->vy = -CHUNK_WIDTH * SQUARE_SIZE;
    game->cx = 0;
    game->cy = 0;

    destroy_all_objects();
    create_tiles(game);
    start_game(game, 15, 15);
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
        Uint8 value, state;
        if (value == 9) {
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
            Uint8 value, state;
            get_tile_info(game->grid[row][col], &value, &state);
            switch (state)  {
                case HIDDEN:
                    texture = get_texture(T_HIDDEN);
                    break;
                case FLAGGED:
                    texture = get_texture(T_FLAG);
                    break;
                case REVEALED:
                    if (value == 9) {
                        texture = get_texture(T_WRONG);
                    } else {
                        texture = get_texture(value + NUMBER_TILE_OFFSET);
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

    reveal_tile(game, row, col);
}

/**
 * Reveals a tile
 * \param game The game to reveal the tile in
 * \param row The row of the tile to reveal
 * \param col The column of the tile to reveal
 */
void reveal_tile(Game *game, int row, int col) {
    store_tile_state(&game->grid[row][col], REVEALED);
    char name[10];
    sprintf(name, "%d_%d", row, col);
    Object *obj = get_object_by_name(name);
    Uint8 value = get_tile_value(game->grid[row][col]);
    if (value == 9) {
        change_object_texture(obj, get_texture(T_WRONG));
        reveal_bombs(game, row, col);
        game->game_over = true;
    } else {
        game->score++;
        change_object_texture(obj, get_texture(value + NUMBER_TILE_OFFSET));
        if (value == 0) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (!in_grid(row+i, col+j)) {
                        continue;
                    }
                    Uint8 state = get_tile_state(game->grid[row+i][col+j]);
                    if (state == HIDDEN) {
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
            char name[10];
            sprintf(name, "%d_%d", row_, col_);
            Object *obj = get_object_by_name(name);
            Uint8 value, state;
            get_tile_info(game->grid[row_][col_], &value, &state);
            if ((row_ == row && col_ == col) || state == REVEALED) {
                continue;
            }
            if (state == FLAGGED && value == 9) {
                continue;
            } else if (state == FLAGGED && value != 9) {
                change_object_texture(obj, get_texture(T_BADFLAG));
            } else if (value == 9) {
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
    Uint8 n = get_tile_value(game->grid[row][col]);
    int flag_count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!in_grid(row+i, col+j)) {
                continue;
            }
            if (get_tile_state(game->grid[row+i][col+j]) == FLAGGED) {
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
            if (get_tile_state(game->grid[row+i][col+j]) == HIDDEN) {
                reveal_tile(game, row+i, col+j);
            }
        }
    }
}