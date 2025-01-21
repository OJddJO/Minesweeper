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
    game->vx = (CHUNK_HEIGHT - BORDER_SIZE) * SQUARE_SIZE;
    game->vy = (CHUNK_WIDTH - BORDER_SIZE) * SQUARE_SIZE;
    game->cx = 1;
    game->cy = 1;

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
    for (int i = 0; i < 3; i++) { // row
        for (int j = 0; j < 3; j++) { // col
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
            if (get_tile_value(grid[row][col]) == 9) {
                continue;
            }

            int count = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (!in_grid(row+i, col+j)) {
                        continue;
                    }
                    if (get_tile_value(grid[row+i][col+j]) == 9) {
                        count++;
                    }
                }
            }
            store_tile_value(&grid[row][col], count);
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
void gen_mines(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH]) {
    for (int i = 0; i < MINES; i++) {
        int row = rand() % CHUNK_HEIGHT;
        int col = rand() % CHUNK_WIDTH;
        if (chunk[row][col] == 9) {
            i--;
        } else {
            chunk[row][col] = 9;
        }
    }   
}

/**
 * Creates the tiles for the full grid
 */
void create_tiles(Game *game) {
    destroy_all_objects();
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
            create_object(name, texture, col * SQUARE_SIZE - game->vx, row * SQUARE_SIZE - game->vy, SQUARE_SIZE, SQUARE_SIZE, false, NULL);
        }
    }
}

/**
 * Starts the game
 * \param game The game to start
 */
void start_game(Game *game, int row, int col) {
    init_grid(game->grid);
    if (!file_exists("saves/1.1.msav")) {
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

        create_tiles(game);
        reveal_tile(game, row, col);
        save_chunks(game);
    } else {
        load_chunks(game, 1, 1); // start chunk is 1, 1
        create_tiles(game);
    }
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
        delete_save();
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
    for (int i = 0; i < MAP_HEIGHT; i++) { // row
        for (int j = 0; j < MAP_WIDTH; j++) { // col
            char name[10];
            sprintf(name, "%d_%d", i, j);
            Object *obj = get_object_by_name(name);
            Uint8 value, state;
            get_tile_info(game->grid[i][j], &value, &state);
            if ((i == row && j == col) || state == REVEALED) {
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

/**
 * Calculates current centered chunk
 * \param game The game to calculate the centered chunk for
 * \param x The variable to store the x coordinate in
 * \param y The variable to store the y coordinate in
 */
void calc_current_centered_chunk(Game *game, int *x, int *y) {
    *x = (int)floor((game->vx + (game->cx * CHUNK_WIDTH + BORDER_SIZE) * SQUARE_SIZE + (CHUNK_WIDTH  * SQUARE_SIZE) / 2) / (CHUNK_WIDTH * SQUARE_SIZE)) - 1;
    *y = (int)floor((game->vy + (game->cy * CHUNK_HEIGHT + BORDER_SIZE) * SQUARE_SIZE + (CHUNK_HEIGHT * SQUARE_SIZE) / 2) / (CHUNK_HEIGHT * SQUARE_SIZE)) - 1;
}

/**
 * Shifts the chunks in the game
 * \param game The game to shift the chunks for
 * \param dx The x direction of the shift
 * \param dy The y direction of the shift
 */
void shift_game_chunks(Game *game, int dx, int dy) {
    Uint8 result[MAP_HEIGHT][MAP_WIDTH];
    init_grid(result);
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            if (in_grid(row + dy * CHUNK_HEIGHT, col + dx * CHUNK_WIDTH)) {
                result[row][col] = game->grid[row + dy * CHUNK_HEIGHT][col + dx * CHUNK_WIDTH];
            }
        }
    }
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            game->grid[row][col] = result[row][col];
        }
    }
}

/**
 * Checks if a mine is valid in the chunk and removes it if it is not
 * \param game The game tile to check the mine for
 * \param chunk The chunk to check the mine for
 * \param row The row of the mine (in the chunk)
 * \param col The column of the mine (in the chunk)
 * \param crow The row of the chunk
 * \param ccol The column of the chunk
 */
void check_mine_valid(Game *game, Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col, int crow, int ccol) {
    //check around the mine if there is already a number
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!in_grid(crow*CHUNK_HEIGHT + row + i, ccol*CHUNK_WIDTH + col + j)) {
                continue;
            }
            Uint8 state = get_tile_state(game->grid[crow*CHUNK_HEIGHT + row + i][ccol*CHUNK_WIDTH + col + j]);
            if (state == REVEALED) {
                chunk[row][col] = 0;
                return;
            }
        }
    }
}

/**
 * Adds a chunk to a running game
 * \param game The game to add the chunk to
 * \param chunk The chunk to add
 * \param row The row where the chunk should be added in the game grid
 * \param col The column where the chunk should be added in the game grid
 * \param crow The row of the chunk to load
 * \param ccol The column of the chunk to load
 */
void add_chunk_to_game(Game *game, int row, int col, int crow, int ccol) {
    Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH];
    char filename[30];
    sprintf(filename, "saves/%d.%d.msav", game->cy + row - 1, game->cx + col - 1);
    bool exists = file_exists(filename);
    if (exists) {
        load_chunk(chunk, crow, ccol);
    } else {
        gen_chunk(chunk);
    }
    for (int i = 0; i < CHUNK_HEIGHT; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {
            if (!exists) {
                bool is_border = i == 0 || i == CHUNK_WIDTH-1 || j == 0 || j == CHUNK_HEIGHT-1;
                if (is_border && chunk[i][j] == 9) {
                    check_mine_valid(game, chunk, i, j, row, col);
                }
            }
            game->grid[row*CHUNK_HEIGHT + i][col*CHUNK_WIDTH + j] = chunk[i][j];
        }
    }
}

/**
 * Post processes the shift of the chunks (generates new chunks, numbers)
 * \param game The game to post process the shift for
 * \param dx The x direction of the shift
 * \param dy The y direction of the shift
 */
void post_process_shift_chunks(Game *game, int dx, int dy) {
    if (dx != 0) {
        int col = dx == 1 ? 2 : 0;
        for (int row = 0; row < 3; row++) {
            int crow = game->cy + row - 1;
            int ccol = game->cx + col - 1;
            add_chunk_to_game(game, row, col, crow, ccol);
        }
    }
    if (dy != 0) {
        int row = dy == 1 ? 2 : 0;
        for (int col = 0; col < 3; col++) {
            int crow = game->cy + row - 1;
            int ccol = game->cx + col - 1;
            add_chunk_to_game(game, row, col, crow, ccol);
        }
    }

    gen_numbers(game->grid);
}

/**
 * Save a single chunk in a file
 * \param chunk The chunk to save
 * \param row The row of the chunk
 * \param col The column of the chunk
 */
void save_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col) {
    char filename[30];
    sprintf(filename, "saves/%d.%d.msav", row, col);
    FILE *file = fopen(filename, "wb");
    fwrite(chunk, sizeof(Uint8), CHUNK_HEIGHT * CHUNK_WIDTH, file);
    fclose(file);
}

/**
 * Saves the chunks of the game
 * \param game The game to save the chunks from
 */
void save_chunks(Game *game) {
    for (int crow = 0; crow < 3; crow++) { // iter through chunk row
        for (int ccol = 0; ccol < 3; ccol++) { // iter through chunk col
            Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH];
            for (int row = 0; row < CHUNK_HEIGHT; row++) {
                for (int col = 0; col < CHUNK_WIDTH; col++) {
                    chunk[row][col] = game->grid[crow*CHUNK_HEIGHT + row][ccol*CHUNK_WIDTH + col];
                }
            }
            save_chunk(chunk, crow + game->cy - 1, ccol + game->cx - 1);
        }
    }
}

/**
 * Loads a single chunk from a file
 * \param chunk The chunk to load
 * \param row The row of the chunk
 * \param col The column of the chunk
 */
void load_chunk(Uint8 chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col) {
    char filename[30];
    sprintf(filename, "saves/%d.%d.msav", row, col);
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            fread(&chunk[row][col], sizeof(Uint8), 1, file);
        }
    }
    fclose(file);
}

/**
 * Loads 9x9 chunks to the game
 * \param game The game to load the chunks to
 * \param row The row of the center chunk to load
 * \param col The column of the center chunk to load
 */
void load_chunks(Game *game, int row, int col) {
    Uint8 chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH];
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            load_chunk(chunks[i+1][j+1], row+i, col+j);
        }
    }
    load_chunks_to_grid(game->grid, chunks);

    // for (int row = 0; row < MAP_HEIGHT; row++) {
    //     for (int col = 0; col < MAP_WIDTH; col++) {
    //         printf("%d ", game->grid[row][col]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}

/**
 * Deletes the save files
 */
void delete_save() {
    DIR *dir = opendir("saves");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char filename[30];
        sprintf(filename, "saves/%s", entry->d_name);
        if (remove(filename) != 0) {
            fprintf(stderr, "Error deleting file %s\n", filename);
            exit(1);
        }
    }
}

/**
 * Checks if a file exists
 * \param filename The name of the file to check
 */
bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
