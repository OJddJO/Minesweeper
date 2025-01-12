#include "game.h"

static void init_grid(Uint8 grid[HEIGHT][WIDTH]);
static void gen_mines(Uint8 grid[HEIGHT][WIDTH]);
static void gen_numbers(Uint8 grid[HEIGHT][WIDTH]);
static void create_tiles();

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

    init_assets();

    Game *game = (Game *)malloc(sizeof(Game));
    init_grid(game->grid);
    gen_mines(game->grid);
    gen_numbers(game->grid);

    init_grid(game->revealed);
    game->score = 0;
    game->game_over = false;

    create_tiles();

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
    get_tile_as_texture("background", tilemap, 2, 4);

    // From 8 - 14
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