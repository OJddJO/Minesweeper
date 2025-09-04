#include "game.h"

static void initAssets();

/**
 * Main function
 */
int main() {
    SSGE_Init("Minesweeper", WIN_W, WIN_H, FPS);
    SSGE_SetBackgroundColor((SSGE_Color){191, 191, 191, 255});
    SSGE_SetWindowIcon("assets/icon.png");

    initAssets();
    SSGE_Font_Create("assets/font.ttf", 20, "font");

    Game game = {0};
    initGame(&game);

    SSGE_Run(NULL, NULL, NULL, NULL);

    SSGE_Quit();

    return 0;
}


/**
 * Initializes the assets
 */
static void initAssets() {
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
