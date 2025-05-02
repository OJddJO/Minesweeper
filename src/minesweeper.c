#include "game.h"

static void init_assets();

static void draw(Game *game);
static void handle_input(SSGE_Event event, Game *game);
static void update(Game *game);

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    SSGE_Init("Minesweeper", WIN_W, WIN_H, FPS);
    SSGE_SetManualUpdate(true);
    SSGE_SetBackgroundColor((SSGE_Color){191, 191, 191, 255});
    SSGE_SetWindowIcon("assets/icon.png");

    srand(time(NULL));
    CreateDirectory("saves", NULL);

    init_assets();
    SSGE_LoadFont("assets/font.ttf", 20, "font");

    Game *game = (Game *)malloc(sizeof(Game));
    init_game(game);

    SSGE_Run(update, draw, handle_input, game);
    save_game(game);

    SSGE_Quit();
    free(game);
    return 0;
}

/**
 * Draws the game
 * \param game The game to draw
 */
static void draw(Game *game) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            char name[10];
            sprintf(name, "%d_%d", row, col);
            SSGE_DrawObject(SSGE_GetObjectByName(name));
        }
    }
    char score[20];
    sprintf(score, "Score: %d", game->score);
    SSGE_DrawText("font", score, 11, WIN_H - 9, (SSGE_Color){0, 0, 0, 255}, SSGE_SW);
    SSGE_DrawText("font", score, 10, WIN_H - 10, (SSGE_Color){255, 255, 255, 255}, SSGE_SW);
    char title[50];
    sprintf(title, "Minesweeper - %s - %s", game->game_over ? "Game Over" : "Playing", score);
    SSGE_SetWindowTitle(title);
    anim(game);
}

/**
 * Updates the game
 * \param game The game to update
 */
static void update(Game *game) {
    if (game->game_over) return;
    if (game->space_pressed && !game->menu) {
        int dx, dy;
        SSGE_GetMousePosition(&dx, &dy);
        dx -= game->mx;
        dy -= game->my;
        if (dx != 0 || dy != 0) {
            for (int row = 0; row < MAP_HEIGHT; row++) {
                for (int col = 0; col < MAP_WIDTH; col++) {
                    char name[10];
                    sprintf(name, "%d_%d", row, col);
                    SSGE_Object *obj = SSGE_GetObjectByName(name);
                    obj->x += dx;
                    obj->y += dy;
                }
            }
            game->vx -= dx;
            game->vy -= dy;
        }
        int x, y;
        calc_current_centered_chunk(game, &x, &y);
        if (x != game->cx || y != game->cy) { // If the centered chunk has changed
            int dx = x - game->cx;
            int dy = y - game->cy;
            save_game(game);
            game->cx = x;
            game->cy = y;

            shift_game_chunks(game, dx, dy);
            post_process_shift_chunks(game, dx, dy);

            game->vx -= dx * CHUNK_WIDTH * SQUARE_SIZE;
            game->vy -= dy * CHUNK_HEIGHT * SQUARE_SIZE;
            create_tiles(game);
        }
        SSGE_ManualUpdate();
    }

    check_upd_anim(game);
    SSGE_GetMousePosition(&game->mx, &game->my);
    game->frame_count++;
}

/**
 * Handles input
 * \param event The event to handle
 * \param game The game to handle the input for
 */
static void handle_input(SSGE_Event event, Game *game) {
    bool update = false;
    switch (event.type) {
        case (SSGE_MOUSEBUTTONDOWN):
            if (game->game_over) {
                delete_save();
                init_game(game);
                SSGE_ManualUpdate();
                return;
            }
            if (!game->menu) {
                int x, y;
                SSGE_GetMousePosition(&x, &y);
                int row = (y + game->vy) / SQUARE_SIZE;
                int col = (x + game->vx) / SQUARE_SIZE;
                uint8_t value, state;
                get_tile_info(game->grid[row][col], &value, &state);
                switch (event.button.button) {
                    case (SSGE_MOUSE_LEFT):
                        if (state == FLAGGED) break;
                        else if (state == HIDDEN) reveal_tile(game, row, col);
                        else if (value >= 1 && value <= 8) reveal_number(game, row, col);
                        update = true;
                        break;
                    case (SSGE_MOUSE_RIGHT):
                        char name[20];
                        sprintf(name, "%d_%d", row, col);
                        SSGE_Object *obj = SSGE_GetObjectByName(name);
                        if (state == HIDDEN) {
                            store_tile_state(&game->grid[row][col], FLAGGED);
                            SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(T_FLAG));
                        } else if (state == FLAGGED) {
                            store_tile_state(&game->grid[row][col], HIDDEN);
                            SSGE_ChangeObjectTexture(obj, SSGE_GetTexture(T_HIDDEN));
                        }
                        update = true;
                        break;
                }
            }
            break;
        case (SSGE_KEYDOWN):
            if (!game->menu) {
                switch (event.key.keysym.sym) {
                    case (SSGE_KEY_SPACE):
                        game->space_pressed = true;
                        break;
                }
            }
            break;
        case (SSGE_KEYUP):
            switch (event.key.keysym.sym) {
                case (SSGE_KEY_SPACE):
                    game->space_pressed = false;
                    break;
                case (SSGE_KEY_s): // Save
                    if (!game->menu) {
                        if (!game->game_over) {
                            save_game(game);
                            game->save_frame = game->frame_count;
                        }
                    }
                    break;
                case (SSGE_KEY_r): // Restart
                    if (!game->menu) {
                        delete_save();
                        init_game(game);
                        update = true;
                    }
                    break;
                case (SSGE_KEY_ESCAPE):
                    game->menu = !game->menu;
                    break;
            }
            break;
    }
    if (update) SSGE_ManualUpdate();
}

/**
 * Initializes the assets
 */
static void init_assets() {
    SSGE_Tilemap *tilemap = SSGE_LoadTilemap("assets/tiles.png", 6, 6, 0, 4, 4);

    // From 0 - 5
    SSGE_GetTileAsTexture("hidden", tilemap, 2, 0);
    SSGE_GetTileAsTexture("mine", tilemap, 2, 1);
    SSGE_GetTileAsTexture("flag", tilemap, 2, 2);
    SSGE_GetTileAsTexture("wrong", tilemap, 2, 3);
    SSGE_GetTileAsTexture("bad_flag", tilemap, 3, 0);
    SSGE_GetTileAsTexture("background", tilemap, 3, 3);

    // From 6 - 13
    SSGE_GetTileAsTexture("1", tilemap, 0, 0);
    SSGE_GetTileAsTexture("2", tilemap, 0, 1);
    SSGE_GetTileAsTexture("3", tilemap, 0, 2);
    SSGE_GetTileAsTexture("4", tilemap, 0, 3);
    SSGE_GetTileAsTexture("5", tilemap, 1, 0);
    SSGE_GetTileAsTexture("6", tilemap, 1, 1);
    SSGE_GetTileAsTexture("7", tilemap, 1, 2);
    SSGE_GetTileAsTexture("8", tilemap, 1, 3);

    SSGE_DestroyTilemap(tilemap);
}
