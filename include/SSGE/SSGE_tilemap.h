#ifndef __SSGE_TILEMAP_H__
#define __SSGE_TILEMAP_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a tilemap
 * \param filename The path to the tilemap
 * \param tileWidth The width of the tile
 * \param tileHeight The height of the tile
 * \param spacing The spacing between tiles
 * \param nbRows The number of rows in the tilemap
 * \param nbCols The number of columns in the tilemap
 * \return The tilemap
 */
SSGEAPI SSGE_Tilemap *SSGE_Tilemap_Create(char *filename, uint16_t tileWidth, uint16_t tileHeight, uint16_t spacing, uint16_t nbRows, uint16_t nbCols);

/**
 * Get a tile from a tilemap
 * \param tilemap The tilemap to use
 * \param row The row of the tile
 * \param col The column of the tile
 * \return The tile
 * \note The tile must be destroyed after use
 */
SSGEAPI SSGE_Tile *SSGE_Tilemap_GetTile(SSGE_Tilemap *tilemap, uint16_t row, uint16_t col);

/**
 * Get a texture from a tilemap
 * \param tilemap The tilemap to use
 * \param row The row of the tile
 * \param col The column of the tile
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Texture *SSGE_Tilemap_GetTileAsTexture(SSGE_Tilemap *tilemap, uint16_t row, uint16_t col, uint32_t *id, char *name);

/**
 * Draw a tile from a tilemap
 * \param tilemap The tilemap to use
 * \param row The row of the tile
 * \param col The column of the tile
 * \param x The x coordinate to draw the tile
 * \param y The y coordinate to draw the tile
 */
SSGEAPI void SSGE_Tilemap_DrawTile(SSGE_Tilemap *tilemap, uint16_t row, uint16_t col, int x, int y);

/**
 * Draw a tile from a tilemap
 * \param tilemap The tilemap to use
 * \param row The row of the tile
 * \param col The column of the tile
 * \param x The x coordinate at which the tile is drawn
 * \param y The y coordinate at which the tile is drawn
 * \param width The width of the drawn tile
 * \param height The height of the drawn tile
 */
SSGEAPI void SSGE_Tilemap_DrawTileSize(SSGE_Tilemap *tilemap, uint16_t row, uint16_t col, int x, int y, uint16_t width, uint16_t height);

/**
 * Draw a tile
 * \param tile The tile to draw
 * \param x The x coordinate to draw the tile
 * \param y The y coordinate to draw the tile
 */
SSGEAPI void SSGE_Tilemap_DrawTileAlt(SSGE_Tile *tile, int x, int y);

/**
 * Draw a tile with the specified width and height
 * \param tile The tile to draw
 * \param x The x coordinate to draw the tile
 * \param y The y coordinate to draw the tile
 * \param width The width of the tile
 * \param height The height of the tile
 */
SSGEAPI void SSGE_Tilemap_DrawTileSizeAlt(SSGE_Tile *tile, int x, int y, uint16_t width, uint16_t height);

/**
 * Destroy a tile
 * \param tile The tile to destroy
 * \note This function does not destroy the tilemap
 */
SSGEAPI void SSGE_Tilemap_DestroyTile(SSGE_Tile *tile);

/**
 * Destroy a tilemap
 * \param tilemap The tilemap to destroy
 */
SSGEAPI void SSGE_Tilemap_Destroy(SSGE_Tilemap *tilemap);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_TILEMAP_H__