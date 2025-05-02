#ifndef __SSGE_TILEMAP_H__
#define __SSGE_TILEMAP_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a tilemap
 * \param filename The path to the tilemap
 * \param tileWidth The width of the tile
 * \param tileHeight The height of the tile
 * \param spacing The spacing between tiles
 * \param nbRows The number of rows in the tilemap
 * \param nbCols The number of columns in the tilemap
 * \return The tilemap
 */
SSGEDECL SSGE_Tilemap *SSGE_LoadTilemap(char *filename, int tileWidth, int tileHeight, int spacing, int nbRows, int nbCols);

/**
 * Gets a tile from a tilemap
 * \param tilemap The tilemap to use
 * \param tileRow The row of the tile
 * \param tileCol The column of the tile
 * \return The tile
 * \note The tile must be destroyed after use
 */
SSGEDECL SSGE_Tile *SSGE_GetTile(SSGE_Tilemap *tilemap, int tileRow, int tileCol);

/**
 * Gets a texture from a tilemap
 * \param name The name of the texture
 * \param tilemap The tilemap to use
 * \param tileRow The row of the tile
 * \param tileCol The column of the tile
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_GetTileAsTexture(char *name, SSGE_Tilemap *tilemap, int tileRow, int tileCol);

/**
 * Draws a tile
 * \param tile The tile to draw
 * \param x The x position to draw the tile
 * \param y The y position to draw the tile
 */
SSGEDECL void SSGE_DrawTile(SSGE_Tile *tile, int x, int y);

/**
 * Draws a tile with the specified width and height
 * \param tile The tile to draw
 * \param x The x position to draw the tile
 * \param y The y position to draw the tile
 * \param width The width of the tile
 * \param height The height of the tile
 */
SSGEDECL void SSGE_DrawTileWithSize(SSGE_Tile *tile, int x, int y, int width, int height);

/**
 * Draws a tile from a tilemap
 * \param tilemap The tilemap to use
 * \param tileRow The row of the tile
 * \param tileCol The column of the tile
 * \param x The x position to draw the tile
 * \param y The y position to draw the tile
 */
SSGEDECL void SSGE_DrawTileFromTilemap(SSGE_Tilemap *tilemap, int tileRow, int tileCol, int x, int y);

/**
 * Destroys a tile
 * \param tile The tile to destroy
 * \note This function does not destroy the tilemap
 */
SSGEDECL void SSGE_DestroyTile(SSGE_Tile *tile);

/**
 * Destroys a tilemap
 * \param tilemap The tilemap to destroy
 */
SSGEDECL void SSGE_DestroyTilemap(SSGE_Tilemap *tilemap);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_TILEMAP_H__