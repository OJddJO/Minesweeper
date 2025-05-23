#include "game.h"

/**
 * Gets the value and state of a tile
 * \param tile The tile to get the info from
 * \param value The variable to store the value in
 * \param state The variable to store the state in
 */
void get_tile_info(uint8_t tile, uint8_t *value, uint8_t *state) {
    *value = (uint8_t)(tile & 0b00001111);
    *state = (uint8_t)((tile & 0b11000000) >> 6);
}

/**
 * Gets the value of a tile
 * \param tile The tile to get the value from
 */
uint8_t get_tile_value(uint8_t tile) {
    return (uint8_t)(tile & 0b00001111);
}

/**
 * Gets the state of a tile
 * \param tile The tile to get the state from
 */
uint8_t get_tile_state(uint8_t tile) {
    return (uint8_t)((tile & 0b11000000) >> 6);
}

/**
 * Stores a value in a tile
 * \param tile The tile to store the value in
 * \param value The value to store
 */
void store_tile_value(uint8_t *tile, uint8_t value) {
    *tile = (uint8_t)((*tile & 0b11000000) | value);
}

/**
 * Stores a state in a tile
 * \param tile The tile to store the state in
 * \param state The state to store
 */
void store_tile_state(uint8_t *tile, uint8_t state) {
    *tile = (uint8_t)((*tile & 0b00001111) | (state << 6));
}

/**
 * Initializes the game structure
 * \param game The game to initialize
 */
void init_game(Game *game) {
    game->menu = false;
    game->menu_alpha = 0;
    game->score = 0;
    game->frame_count = 0;
    game->save_frame = 0;
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
void init_grid(uint8_t grid[MAP_HEIGHT][MAP_WIDTH]) {
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
void load_chunks_to_grid(uint8_t grid[MAP_HEIGHT][MAP_WIDTH], uint8_t chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH]) {
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
void gen_numbers(uint8_t grid[MAP_HEIGHT][MAP_WIDTH]) {
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
void gen_chunk(uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH]) {
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
void gen_mines(uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH]) {
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
    SSGE_DestroyAllObjects();
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            char name[20];
            sprintf(name, "%d_%d", row, col);
            SSGE_Texture *texture;
            uint8_t value, state;
            get_tile_info(game->grid[row][col], &value, &state);
            switch (state)  {
                case HIDDEN:
                    texture = SSGE_GetTexture(T_HIDDEN);
                    break;
                case FLAGGED:
                    texture = SSGE_GetTexture(T_FLAG);
                    break;
                case REVEALED:
                    if (value == 9) {
                        texture = SSGE_GetTexture(T_WRONG);
                    } else {
                        texture = SSGE_GetTexture(value + NUMBER_TILE_OFFSET);
                    }
                    break;
                default:
                    texture = SSGE_GetTexture(T_HIDDEN);
                    break;
            }
            SSGE_CreateObject(name, texture, col * SQUARE_SIZE - game->vx, row * SQUARE_SIZE - game->vy, SQUARE_SIZE, SQUARE_SIZE, false, NULL, NULL);
        }
    }
}

/**
 * Starts the game
 * \param game The game to start
 */
void start_game(Game *game, int row, int col) {
    init_grid(game->grid);
    if (!file_exists("saves/data.msav")) {
        uint8_t chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH];
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
        load_data(game);
        load_chunks(game, game->cx, game->cy);
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
    SSGE_Object *obj = SSGE_GetObjectByName(name);
    uint8_t value = get_tile_value(game->grid[row][col]);
    if (value == 9) {
        SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(T_WRONG));
        reveal_bombs(game, row, col);
        game->game_over = true;
    } else {
        game->score++;
        SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(value + NUMBER_TILE_OFFSET));
        if (value == 0) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (!in_grid(row+i, col+j)) {
                        continue;
                    }
                    uint8_t state = get_tile_state(game->grid[row+i][col+j]);
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
            SSGE_Object *obj = SSGE_GetObjectByName(name);
            uint8_t value, state;
            get_tile_info(game->grid[i][j], &value, &state);
            if ((i == row && j == col) || state == REVEALED) {
                continue;
            }
            if (state == FLAGGED && value == 9) {
                continue;
            } else if (state == FLAGGED && value != 9) {
                SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(T_BADFLAG));
            } else if (value == 9) {
                SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(T_MINE));
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
    uint8_t n = get_tile_value(game->grid[row][col]);
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
    uint8_t result[MAP_HEIGHT][MAP_WIDTH];
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
void check_mine_valid(Game *game, uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col, int crow, int ccol) {
    //check around the mine if there is already a number
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!in_grid(crow*CHUNK_HEIGHT + row + i, ccol*CHUNK_WIDTH + col + j)) {
                continue;
            }
            uint8_t state = get_tile_state(game->grid[crow*CHUNK_HEIGHT + row + i][ccol*CHUNK_WIDTH + col + j]);
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
    uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH];
    char filename[50];
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
 * Saves game datas
 * \param game The game to save
 */
void save_data(Game *game) {
    FILE *file = fopen("saves/data.msav", "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file saves/data.msav\n");
        exit(1);
    }
    fwrite(&game->score, sizeof(uint32_t), 1, file);
    fwrite(&game->game_over, sizeof(bool), 1, file);
    fwrite(&game->vx, sizeof(int), 1, file);
    fwrite(&game->vy, sizeof(int), 1, file);
    fwrite(&game->cy, sizeof(int), 1, file);
    fwrite(&game->cx, sizeof(int), 1, file);
    fclose(file);
}

/**
 * Loads game datas
 * \param game The game to load
 */
void load_data(Game *game) {
    FILE *file = fopen("saves/data.msav", "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file saves/data.msav\n");
        exit(1);
    }
    fread(&game->score, sizeof(uint32_t), 1, file);
    fread(&game->game_over, sizeof(bool), 1, file);
    fread(&game->vx, sizeof(int), 1, file);
    fread(&game->vy, sizeof(int), 1, file);
    fread(&game->cx, sizeof(int), 1, file);
    fread(&game->cy, sizeof(int), 1, file);
    fclose(file);
}

/**
 * Save a single chunk in a file
 * \param chunk The chunk to save
 * \param row The row of the chunk
 * \param col The column of the chunk
 */
void save_chunk(uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col) {
    char filename[50];
    sprintf(filename, "saves/%d.%d.msav", row, col);
    FILE *file = fopen(filename, "wb");
    fwrite(chunk, sizeof(uint8_t), CHUNK_HEIGHT * CHUNK_WIDTH, file);
    fclose(file);
}

/**
 * Saves the chunks of the game
 * \param game The game to save the chunks from
 */
void save_chunks(Game *game) {
    for (int crow = 0; crow < 3; crow++) { // iter through chunk row
        for (int ccol = 0; ccol < 3; ccol++) { // iter through chunk col
            uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH];
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
void load_chunk(uint8_t chunk[CHUNK_HEIGHT][CHUNK_WIDTH], int row, int col) {
    char filename[30];
    sprintf(filename, "saves/%d.%d.msav", row, col);
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            fread(&chunk[row][col], sizeof(uint8_t), 1, file);
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
    uint8_t chunks[3][3][CHUNK_HEIGHT][CHUNK_WIDTH];
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
        char filename[300];
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

/**
 * Checks if the game saved animation need to be updated
 * \param game The game to check the animation for
 */
void check_upd_save_anim(Game *game) {
    int df = game->frame_count - game->save_frame;
    if (df > SAVE_ANIM_FRAMES) {
        return;
    }
    if (df % 2 == 0 && df <= SAVE_ANIM_FRAMES) {
        game->update_save_anim = true;
        SSGE_ManualUpdate();
    }
}

/**
 * Renders the frame of the save animation
 * \param game The game to render the frame for
 */
void save_anim(Game *game) {
    int df = game->frame_count - game->save_frame;
    if (df > SAVE_ANIM_FRAMES) {
        return;
    }
    if (df < SAVE_ANIM_FRAMES/2) { // fade in
        int alpha = 255 * df / (SAVE_ANIM_FRAMES/2);
        SSGE_DrawText("font", "Game saved", 11, 11, (SSGE_Color){0, 0, 0, alpha}, SSGE_NW);
        SSGE_DrawText("font", "Game saved", 10, 10, (SSGE_Color){255, 255, 255, alpha}, SSGE_NW);
    } else { // fade out
        int alpha = 255 - 255 * (df - SAVE_ANIM_FRAMES/2) / (SAVE_ANIM_FRAMES/2);
        SSGE_DrawText("font", "Game saved", 11, 11, (SSGE_Color){0, 0, 0, alpha}, SSGE_NW);
        SSGE_DrawText("font", "Game saved", 10, 10, (SSGE_Color){255, 255, 255, alpha}, SSGE_NW);
    }
}

/**
 * Checks if the game menu animation need to be updated
 * \param game The game to check the animation for
 */
void check_upd_menu_fade(Game *game) {
    if ((game->menu && game->menu_alpha != MENU_FADE_MAX_ALPHA) || (!game->menu && game->menu_alpha != 0)) {
        game->update_menu_anim = true;
        SSGE_ManualUpdate();
    }
}

/**
 * Fade the game menu
 * \param game The game to fade the menu for
 */
void menu_fade(Game *game) {
    game->menu_alpha += (short)(game->menu ? MENU_ALPHA_STEP : -MENU_ALPHA_STEP);
    if (game->menu_alpha <= 0) return;
    SSGE_FillRect(0, 0, WIN_W, WIN_H, (SSGE_Color){0, 0, 0, game->menu_alpha});
    short alpha = game->menu_alpha * 255 / MENU_FADE_MAX_ALPHA;
    SSGE_DrawText("font", "Game paused", 10, 10, (SSGE_Color){255, 255, 255, alpha}, SSGE_NW);
    SSGE_DrawText("font", "ESC      : Continue", 10, WIN_H - 110, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
    SSGE_DrawText("font", "SPACE    : Drag the grid", 10, WIN_H - 90, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
    SSGE_DrawText("font", "LMB      : Reveal tile", 10, WIN_H - 70, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
    SSGE_DrawText("font", "RMB      : Flag tile", 10, WIN_H - 50, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
    SSGE_DrawText("font", "S        : Save game", 10, WIN_H - 30, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
    SSGE_DrawText("font", "R        : Reset game", 10, WIN_H - 10, (SSGE_Color){255, 255, 255, alpha}, SSGE_SW);
}