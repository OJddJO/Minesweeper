#include "game.h"

static void init_assets();

static void draw(Game *game);
static void handle_input(SDL_Event event, Game *game);
static void update(Game *game);

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    engine_init("Minesweeper", WIN_W, WIN_H, FPS);
    set_manual_update(true);
    set_background_color((SDL_Color){191, 191, 191, 255});
    set_window_icon("assets/icon.png");

    srand(time(NULL));
    CreateDirectory("saves", NULL);

    init_assets();
    load_font("assets/font.ttf", 20, "font");

    Game *game = (Game *)malloc(sizeof(Game));
    game->menu = false;
    game->menu_alpha = 0;
    init_game(game);

    engine_run(update, draw, handle_input, game);
    save_game(game);

    destroy_all_objects();
    destroy_all_textures();
    close_all_fonts();
    engine_quit();
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
            draw_object(get_object_by_name(name));
        }
    }
    char score[20];
    sprintf(score, "Score: %d", game->score);
    draw_text("font", score, 11, WIN_H - 9, (SDL_Color){0, 0, 0, 255}, SW);
    draw_text("font", score, 10, WIN_H - 10, (SDL_Color){255, 255, 255, 255}, SW);
    char title[50];
    sprintf(title, "Minesweeper - %s - %s", game->game_over ? "Game Over" : "Playing", score);
    set_window_title(title);
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
        get_mouse_position(&dx, &dy);
        dx -= game->mx;
        dy -= game->my;
        if (dx != 0 || dy != 0) {
            for (int row = 0; row < MAP_HEIGHT; row++) {
                for (int col = 0; col < MAP_WIDTH; col++) {
                    char name[10];
                    sprintf(name, "%d_%d", row, col);
                    Object *obj = get_object_by_name(name);
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
        manual_update();
    }

    check_upd_anim(game);
    get_mouse_position(&game->mx, &game->my);
    game->frame_count++;
}

/**
 * Handles input
 * \param event The event to handle
 * \param game The game to handle the input for
 */
static void handle_input(SDL_Event event, Game *game) {
    bool update = false;
    switch (event.type) {
        case (SDL_MOUSEBUTTONDOWN):
            if (game->game_over) {
                delete_save();
                init_game(game);
                manual_update();
                return;
            }
            if (game->menu) {

            } else {
                int x, y;
                get_mouse_position(&x, &y);
                int row = (y + game->vy) / SQUARE_SIZE;
                int col = (x + game->vx) / SQUARE_SIZE;
                Uint8 value, state;
                get_tile_info(game->grid[row][col], &value, &state);
                switch (event.button.button) {
                    case (SDL_BUTTON_LEFT):
                        if (state == FLAGGED) break;
                        else if (state == HIDDEN) reveal_tile(game, row, col);
                        else if (value >= 1 && value <= 8) reveal_number(game, row, col);
                        update = true;
                        break;
                    case (SDL_BUTTON_RIGHT):
                        char name[10];
                        sprintf(name, "%d_%d", row, col);
                        Object *obj = get_object_by_name(name);
                        if (state == HIDDEN) {
                            store_tile_state(&game->grid[row][col], FLAGGED);
                            change_object_texture(obj, get_texture(T_FLAG));
                        } else if (state == FLAGGED) {
                            store_tile_state(&game->grid[row][col], HIDDEN);
                            change_object_texture(obj, get_texture(T_HIDDEN));
                        }
                        update = true;
                        break;
                }
            }
            break;
        case (SDL_KEYDOWN):
            if (!game->menu) {
                switch (event.key.keysym.sym) {
                    case (SDLK_SPACE):
                        game->space_pressed = true;
                        break;
                }
            }
            break;
        case (SDL_KEYUP):
            switch (event.key.keysym.sym) {
                case (SDLK_SPACE):
                    game->space_pressed = false;
                    break;
                case (SDLK_s): // Save
                    if (!game->menu) {
                        if (!game->game_over) {
                            save_game(game);
                            game->save_frame = game->frame_count;
                        }
                    }
                    break;
                case (SDLK_r): // Restart
                    if (!game->menu) {
                        delete_save();
                        init_game(game);
                        update = true;
                    }
                    break;
                case (SDLK_ESCAPE):
                    game->menu = !game->menu;
                    break;
            }
            break;
    }
    if (update) manual_update();
}

/**
 * Initializes the assets
 */
static void init_assets() {
    Tilemap *tilemap = load_tilemap("assets/tiles.png", 6, 6, 0, 4, 4);

    // From 1 - 7
    get_tile_as_texture("hidden", tilemap, 2, 0);
    get_tile_as_texture("mine", tilemap, 2, 1);
    get_tile_as_texture("flag", tilemap, 2, 2);
    get_tile_as_texture("wrong", tilemap, 2, 3);
    get_tile_as_texture("bad_flag", tilemap, 3, 0);
    get_tile_as_texture("background", tilemap, 3, 3);

    // From 7 - 13
    get_tile_as_texture("1", tilemap, 0, 0);
    get_tile_as_texture("2", tilemap, 0, 1);
    get_tile_as_texture("3", tilemap, 0, 2);
    get_tile_as_texture("4", tilemap, 0, 3);
    get_tile_as_texture("5", tilemap, 1, 0);
    get_tile_as_texture("6", tilemap, 1, 1);
    get_tile_as_texture("7", tilemap, 1, 2);
    get_tile_as_texture("8", tilemap, 1, 3);

    destroy_tilemap(tilemap);
}
