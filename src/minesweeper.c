#include "game.h"

static void init_game(Game *game);
static void init_grid(Uint8 grid[HEIGHT][WIDTH]);
static void gen_mines(Uint8 grid[HEIGHT][WIDTH]);
static void gen_numbers(Uint8 grid[HEIGHT][WIDTH]);
static void create_tiles();
static void start_game(Game *game, int row, int col);
static void reveal_tile(Game *game, int row, int col);
static void reveal_bombs(Game *game, int row, int col);
static void reveal_number(Game *game, int row, int col);

static void init_assets();

static void update(Game *game);
static void draw(Game *game);
static void handle_input(SDL_Event event, Game *game);

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    engine_init("Minesweeper", WIN_W, WIN_H, 60);
    set_manual_update(true);
    set_background_color((SDL_Color){191, 191, 191, 255});
    set_window_icon("assets/icon.png");

    srand(time(NULL));

    init_assets();

    Game *game = (Game *)malloc(sizeof(Game));
    init_game(game);

    // for (int row = 0; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         printf("%d ", game->grid[row][col]);
    //     }
    //     printf("\n");
    // }

    engine_run(update, draw, handle_input, game);

    engine_quit();
    free(game);
    return 0;
}

/**
 * Updates the game
 * \param game The game to update
 */
static void update(Game *game) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            char name[6];
            sprintf(name, "%d_%d", row, col);
            Object *obj = get_object_by_name(name);
        }
    }
}

/**
 * Draws the game
 * \param game The game to draw
 */
static void draw(Game *game) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            char name[6];
            sprintf(name, "%d_%d", row, col);
            draw_object(get_object_by_name(name));
        }
    }
}

/**
 * Handles input
 * \param event The event to handle
 * \param game The game to handle the input for
 */
static void handle_input(SDL_Event event, Game *game) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (game->game_over) {
            init_game(game);
            manual_update();
            return;
        } else if (event.button.button == SDL_BUTTON_LEFT) {
            int x, y;
            get_mouse_position(&x, &y);
            int row = y / SQUARE_SIZE;
            int col = x / SQUARE_SIZE;

            if (game->start) start_game(game, row, col);

            if (game->state[row][col] == FLAGGED) {
                return;
            }

            if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
                if (game->state[row][col] == HIDDEN) reveal_tile(game, row, col);
                else if (game->grid[row][col] >= 1 && game->grid[row][col] <= 8) reveal_number(game, row, col);
            }
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            int x, y;
            get_mouse_position(&x, &y);
            int row = y / SQUARE_SIZE;
            int col = x / SQUARE_SIZE;
            if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
                if (game->state[row][col] == HIDDEN) {
                    game->state[row][col] = FLAGGED;

                    char name[6];
                    sprintf(name, "%d_%d", row, col);
                    Object *obj = get_object_by_name(name);
                    change_object_texture(obj, get_texture_by_name("flag"));
                } else if (game->state[row][col] == FLAGGED) {
                    game->state[row][col] = HIDDEN;

                    char name[6];
                    sprintf(name, "%d_%d", row, col);
                    Object *obj = get_object_by_name(name);
                    change_object_texture(obj, get_texture_by_name("hidden"));
                }
            }
        }
        manual_update();
    }
}

/**
 * Initializes the assets
 */
static void init_assets() {
    Tilemap *tilemap = create_tilemap("assets/tiles.png", 6, 6, 0, 5, 5);

    // From 1 - 7
    get_tile_as_texture("flag", tilemap, 0, 0);
    get_tile_as_texture("mine", tilemap, 0, 1);
    get_tile_as_texture("hidden", tilemap, 2, 0);
    get_tile_as_texture("hovered", tilemap, 2, 1);
    get_tile_as_texture("revealed", tilemap, 2, 2);
    get_tile_as_texture("wrong", tilemap, 2, 3);
    get_tile_as_texture("bad_flag", tilemap, 2, 4);
    get_tile_as_texture("background", tilemap, 3, 4);

    // From 9 - 15
    get_tile_as_texture("1", tilemap, 0, 2);
    get_tile_as_texture("2", tilemap, 0, 3);
    get_tile_as_texture("3", tilemap, 0, 4);
    get_tile_as_texture("4", tilemap, 1, 0);
    get_tile_as_texture("5", tilemap, 1, 1);
    get_tile_as_texture("6", tilemap, 1, 2);
    get_tile_as_texture("7", tilemap, 1, 3);
    get_tile_as_texture("8", tilemap, 1, 4);
}

/**
 * Initializes the game structure
 * \param game The game to initialize
 */
static void init_game(Game *game) {
    init_grid(game->state);
    game->score = 0;
    game->start = true;
    game->game_over = false;

    destroy_all_objects();
    create_tiles();
}

/**
 * Initializes the grid with 0s
 * \param grid The grid to initialize
 */
static void init_grid(Uint8 grid[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            grid[row][col] = 0;
        }
    }
}

/**
 * Generates the mines in the grid
 * \param grid The grid to generate the mines in
 */
static void gen_mines(Uint8 grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < MINES; i++) {
        int row = rand() % HEIGHT;
        int col = rand() % WIDTH;
        if (grid[row][col] == 9) {
            i--;
        } else {
            grid[row][col] = 9;
        }
    }
}

/**
 * Generates the numbers in the grid
 * \param grid The grid to generate the numbers in
 */
static void gen_numbers(Uint8 grid[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (grid[row][col] == 9) {
                continue;
            }

            int count = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (row + i < 0 || row + i >= HEIGHT || col + j < 0 || col + j >= WIDTH) {
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
 * Creates the tiles
 */
static void create_tiles() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            char name[6];
            sprintf(name, "%d_%d", row, col);
            create_object(name, get_texture_by_name("hidden"), col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, true, NULL);
        }
    }
}

/**
 * Starts the game
 * \param game The game to start
 */
static void start_game(Game *game, int row, int col) {
    init_grid(game->grid);
    gen_mines(game->grid);
    gen_numbers(game->grid);

    while (game->grid[row][col] != 0) {
        init_grid(game->grid);
        gen_mines(game->grid);
        gen_numbers(game->grid);
    }

    game->start = false;
}

/**
 * Reveals a tile
 * \param game The game to reveal the tile in
 * \param row The row of the tile to reveal
 * \param col The column of the tile to reveal
 */
static void reveal_tile(Game *game, int row, int col) {
    game->state[row][col] = REVEALED;
    char name[6];
    sprintf(name, "%d_%d", row, col);
    Object *obj = get_object_by_name(name);
    if (game->grid[row][col] == 9) {
        change_object_texture(obj, get_texture_by_name("wrong"));
        reveal_bombs(game, row, col);
        game->game_over = true;
    } else {
        change_object_texture(obj, get_texture_by_id(game->grid[row][col] + NUMBER_TILE_OFFSET));
        if (game->grid[row][col] == 0) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (row + i < 0 || row + i >= HEIGHT || col + j < 0 || col + j >= WIDTH) {
                        continue;
                    }
                    if (game->state[row+i][col+j] == HIDDEN) {
                        game->state[row+i][col+j] = REVEALED;
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
static void reveal_bombs(Game *game, int row, int col) {
    for (int row_ = 0; row_ < HEIGHT; row_++) {
        for (int col_ = 0; col_ < WIDTH; col_++) {
            if (row_ == row && col_ == col) {
                continue;
            }
            if (game->state[row_][col_] == REVEALED) {
                continue;
            }
            if (game->state[row_][col_] == FLAGGED && game->grid[row_][col_] != 9) {
                char name[6];
                sprintf(name, "%d_%d", row_, col_);
                Object *obj = get_object_by_name(name);
                change_object_texture(obj, get_texture_by_name("bad_flag"));
            }else if (game->grid[row_][col_] == 9) {
                char name[6];
                sprintf(name, "%d_%d", row_, col_);
                Object *obj = get_object_by_name(name);
                change_object_texture(obj, get_texture_by_name("mine"));
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
static void reveal_number(Game *game, int row, int col) {
    int n = game->grid[row][col];
    int flag_count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (row + i < 0 || row + i >= HEIGHT || col + j < 0 || col + j >= WIDTH) {
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
            if (row + i < 0 || row + i >= HEIGHT || col + j < 0 || col + j >= WIDTH) {
                continue;
            }
            if (game->state[row+i][col+j] == HIDDEN) {
                reveal_tile(game, row+i, col+j);
            }
        }
    }
}