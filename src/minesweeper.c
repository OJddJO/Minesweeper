#include "game.h"

/**
 * Initializes the assets
 */
inline static void initAssets() {
    SSGE_Tilemap *tilemap = SSGE_Tilemap_Create("assets/tiles.png", 6, 6, 0, 4, 4);

    uint32_t id;
    // From 0 - 5
    SSGE_Tilemap_GetTileAsTexture(tilemap, 2, 0, &id, "hidden");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 2, 1, &id, "mine");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 2, 2, &id, "flag");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 2, 3, &id, "wrong");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 3, 0, &id, "bad_flag");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 3, 3, &id, "background");

    // From 6 - 13
    SSGE_Tilemap_GetTileAsTexture(tilemap, 0, 0, &id, "1");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 0, 1, &id, "2");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 0, 2, &id, "3");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 0, 3, &id, "4");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 1, 0, &id, "5");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 1, 1, &id, "6");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 1, 2, &id, "7");
    SSGE_Tilemap_GetTileAsTexture(tilemap, 1, 3, &id, "8");

    SSGE_Tilemap_Destroy(tilemap);
}

static void update(Game *game);
static void draw(Game *game);
static void eventHandler(SSGE_Event event, Game *game);

/**
 * Main function
 */
int main() {
    SSGE_Init("Minesweeper", WIN_W, WIN_H, FPS);
    SSGE_SetBackgroundColor((SSGE_Color){191, 191, 191, 255});
    SSGE_SetWindowIcon("assets/icon.png");
    SSGE_SetVSync(true);

    initAssets();
    SSGE_Font_Create("assets/font.ttf", 20, "font");

    Game game = {0};
    initGame(&game);

    game.start = clock();

    SSGE_Run((SSGE_UpdateFunc)update, (SSGE_DrawFunc)draw, (SSGE_EventHandler)eventHandler, &game);

    SSGE_Quit();

    return 0;
}

static void update(Game *game) {
    ++game->update;
}

static void draw(Game *game) {
    if (game->debug) {
        double fps = (double)++game->frame / (double)(clock() - game->start) * CLOCKS_PER_SEC;
        double ups = game->update / (double)(clock() - game->start) * CLOCKS_PER_SEC;
        char fptchar[100];
        sprintf(fptchar, "FPS: %.2f | UPS: %.2f", fps, ups);
        SSGE_Text_Draw("font", fptchar, 4, 4, (SSGE_Color){0, 0, 0, 255}, SSGE_NW);
        SSGE_Text_Draw("font", fptchar, 2, 2, (SSGE_Color){255, 255, 255, 255}, SSGE_NW);
    } else {
        ++game->frame;
        char score[50];
        sprintf(score, "Score: %llu", game->score);
        SSGE_Text_Draw("font", score, 4, 4, (SSGE_Color){0, 0, 0, 255}, SSGE_NW);
        SSGE_Text_Draw("font", score, 2, 2, (SSGE_Color){255, 255, 255, 255}, SSGE_NW);
    }
}

static void eventHandler(SSGE_Event event, Game *game) {
    switch (event.type) {
        case SSGE_EVENT_MOUSEBUTTONDOWN:
            int x, y;
            SSGE_GetMousePosition(&x, &y);
            int64_t lrow = (y + game->vy) / TILE_SIZE,
                    lcol = (x + game->vx) / TILE_SIZE;
            switch (event.button.button) {
                case SSGE_MOUSE_LEFT:
                    revealTile(game, lrow, lcol);
                    break;
                case SSGE_MOUSE_RIGHT:
                    flagTile(game, lrow, lcol);
                    break;
            }
            break;
        case SSGE_EVENT_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SSGE_SCANCODE_F5:
                    game->debug = !game->debug;
                    break;
            }
    }
}