#include "game.h"

void printChunk(Chunk chunk) {
    for (int8_t row = 0; row < CHUNK_HEIGHT; row++) {
        for (int8_t col = 0; col < CHUNK_WIDTH; col++) {
            printf("%u ", chunk[row][col]);
        }
        puts("");
    }
}

void printMap(Map map) {
    for (int32_t lrow = 0; lrow < MAP_HEIGHT * CHUNK_HEIGHT; lrow++) {
        for (int32_t lcol = 0; lcol < MAP_WIDTH * CHUNK_WIDTH; lcol++) {
            int8_t crow, ccol, row, col;
            linearToChunk(lrow, lcol, &crow, &ccol, &row, &col);
            printf("%u ", map[crow][ccol][row][col]);
        }
        puts("");
    }
}

/**
 * Generates the mines in a chunk
 * \param chunk The chunk to generate the mines in
 */
inline static void genMines(Chunk chunk) {
    uint8_t i = 0;
    while (i < MINES) {
        int row = rand() % CHUNK_HEIGHT;
        int col = rand() % CHUNK_WIDTH;
        if (chunk[row][col] != 9) {
            chunk[row][col] = 9;
            ++i;
        }
    }
}

/**
 * Generates a chunk
 * \param chunk The chunk to generate
 */
void genChunk(Chunk chunk) {
    for (int8_t row = 0; row < CHUNK_HEIGHT; row++) {
        for (int8_t col = 0; col < CHUNK_WIDTH; col++) {
            chunk[row][col] = 0;
        }
    }
    genMines(chunk);
}

/**
 * Generates the numbers in the map
 * \param map The map to generate the numbers in
 */
inline static void genNumbers(Map map) {
    for (int32_t lrow = 0; lrow < CHUNK_HEIGHT * MAP_HEIGHT; lrow++) {
        for (int32_t lcol = 0; lcol < CHUNK_WIDTH * MAP_WIDTH; lcol++) {
            int8_t crow, ccol, row, col;
            linearToChunk(lrow, lcol, &crow, &ccol, &row, &col);
            
            // Skip if it's a mine
            if (map[crow][ccol][row][col] == 9) continue;
            
            uint8_t count = 0;
            int8_t crow_, ccol_, row_, col_;
            for (int8_t i = -1; i < 2; i++) {
                for (int8_t j = -1; j < 2; j++) {
                    if ((i == 0 && j == 0) || outOfMap(crow, ccol, row + i, col + j)) continue;

                    linearToChunk(lrow + i, lcol + j, &crow_, &ccol_, &row_, &col_);
                    if (getTileValue(map[crow_][ccol_][row_][col_]) == 9) ++count;
                }
            }
            storeTileValue(&map[crow][ccol][row][col], count);
        }
    }
}

void genMap(Map map) {
    for (int8_t row = 0; row < MAP_HEIGHT; row++) {
        for (int8_t col = 0; col < MAP_WIDTH; col++) {
            genChunk(map[row][col]);
        }
    }
    genNumbers(map);
}

void createTiles(Game *game) {
    for (int8_t crow = 0; crow < MAP_HEIGHT; crow++)
    for (int8_t ccol = 0; ccol < MAP_WIDTH; ccol++)
    for (int8_t row = 0; row < CHUNK_HEIGHT; row++)
    for (int8_t col = 0; col < CHUNK_WIDTH; col++)
    {
        int32_t lrow, lcol;
        chunkToLinear(crow, ccol, row, col, &lrow, &lcol);
        int x = lcol * TILE_SIZE - game->vx,
            y = lrow * TILE_SIZE - game->vy;
        SSGE_Object *obj = SSGE_Object_Create(&game->ids[lrow][lcol], NULL, x, y, TILE_SIZE, TILE_SIZE, false, NULL, NULL);
        
        uint8_t value, state;
        getTileInfo(game->map[crow][ccol][row][col], &value, &state);
        SSGE_Texture *texture;
        switch (state) {
            case S_HIDDEN:
                texture = SSGE_Texture_Get(T_HIDDEN);
                break;
            case S_FLAGGED:
                texture = SSGE_Texture_Get(T_FLAG);
                break;
            case S_REVEALED:
                texture = SSGE_Texture_Get(value == 9 ? T_WRONG : value + NUMBER_TILE_OFFSET);
                break;
            default:
                texture = SSGE_Texture_Get(T_HIDDEN);
                break;
        }

        SSGE_Object_BindTexture(obj, texture);
    }
}

void initGame(Game *game) {
    for (int8_t row = 0; row < MAP_HEIGHT; row++) {
        for (int8_t col = 0; col < MAP_WIDTH; col++) {
            genChunk(game->map[col][row]);
        }
    }
    genNumbers(game->map);

    int32_t lrow = MAP_HEIGHT * CHUNK_HEIGHT / 2,
            lcol = MAP_WIDTH * CHUNK_WIDTH / 2;
    int8_t  crow, ccol, row, col;
    linearToChunk(lrow, lcol, &crow, &ccol, &row, &col);
    while (getTileValue(game->map[crow][ccol][row][col]) != 0) {
        genChunk(game->map[crow][ccol]);
        genNumbers(game->map);
    }
    game->vx = (CHUNK_HEIGHT - BORDER_SIZE) * TILE_SIZE;
    game->vy = (CHUNK_WIDTH - BORDER_SIZE) * TILE_SIZE;

    createTiles(game);
    revealTile(game, lrow, lcol);
}

void revealTile(Game *game, int32_t lrow, int32_t lcol) {
    int8_t crow, ccol, row, col;
    linearToChunk(lrow, lcol, &crow, &ccol, &row, &col);
    if (getTileState(game->map[crow][ccol][row][col])) return;
    storeTileState(&game->map[crow][ccol][row][col], S_REVEALED);
    SSGE_Object *obj = SSGE_Object_Get(game->ids[lrow][lcol]);
    uint8_t value = getTileValue(game->map[crow][ccol][row][col]);
    if (value == 9) {
        // end game
    } else {
        ++game->score;
        SSGE_Object_BindTexture(obj, SSGE_Texture_Get(value + NUMBER_TILE_OFFSET));
        if (value == 0) {
            int8_t crow_, ccol_, row_, col_;
            for (int8_t i = -1; i < 2; i++) {
                for (int8_t j = -1; j < 2; j++) {
                    if (outOfMap(crow, ccol, row + i, col + j)) continue;
                    linearToChunk(lrow + i, lcol + j, &crow_, &ccol_, &row_, &col_);
                    uint8_t state = getTileState(game->map[crow_][ccol_][row_][col_]);
                    if (state == S_HIDDEN) revealTile(game, lrow + i, lcol + j);
                }
            }
        }
    }
}

void flagTile(Game *game, int32_t lrow, int32_t lcol) {
    int8_t crow, ccol, row, col;
    linearToChunk(lrow, lcol, &crow, &ccol, &row, &col);
    uint8_t state = getTileState(game->map[crow][ccol][row][col]);
    SSGE_Object *obj = SSGE_Object_Get(game->ids[lrow][lcol]);
    switch (state) {
        case S_HIDDEN:
            storeTileState(&game->map[crow][ccol][row][col], S_FLAGGED);
            SSGE_Object_BindTexture(obj, SSGE_Texture_Get(T_FLAG));
            break;
        case S_FLAGGED:
            storeTileState(&game->map[crow][ccol][row][col], S_HIDDEN);
            SSGE_Object_BindTexture(obj, SSGE_Texture_Get(S_HIDDEN));
            break;
    }
}