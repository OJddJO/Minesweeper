#ifndef __SSGE_TEXTURE_H__
#define __SSGE_TEXTURE_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a texture
 * \param id Where to store the id of the texture
 * \param filename The path to the texture
 * \param name The name of the texture
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Texture *SSGE_Texture_Create(uint32_t *id, char *filename, char *name);

/**
 * Get a texture by id
 * \param id The id of the texture
 * \return The texture
 */
SSGEAPI SSGE_Texture *SSGE_Texture_Get(uint32_t id);

/**
 * Get a texture by name
 * \param name The name of the texture
 * \return The texture
 */
SSGEAPI SSGE_Texture *SSGE_Texture_GetName(char *name);

/**
 * Set the anchor of a texture
 * \param texture The texture to set the anchor of
 * \param x The anchor's x coordinate
 * \param y The anchor's y coordinate
 */
SSGEAPI void SSGE_Texture_Anchor(SSGE_Texture *texture, int x, int y);

/**
 * Draw a texture
 * \param texture The texture to draw
 * \param x The x coordinate at which the texture is drawn
 * \param y The y coordinate at which the texture is drawn
 * \param width The width of the texture
 * \param height The height of the texture
 */
SSGEAPI void SSGE_Texture_Draw(SSGE_Texture *texture, int x, int y, int width, int height);

/**
 * Draw a texture with more options
 * \param texture The texture to draw
 * \param x The x coordinate at which the texture is drawn
 * \param y The y coordinate at which the texture is drawn
 * \param width The width of the texture
 * \param height The height of the texture
 * \param angle The angle in degrees to rotate the texture (clockwise rotation)
 * \param center The center of the rotation
 * \param flip The flip to apply to the texture
 */
SSGEAPI void SSGE_Texture_DrawEx(SSGE_Texture *texture, int x, int y, int width, int height, double angle, SSGE_Point center, SSGE_Flip flip);

/**
 * Destroy a texture
 * \param id The id of the texture
 */
SSGEAPI void SSGE_Texture_Destroy(uint32_t id);

/**
 * Destroy a texture
 * \param name The name of the texture
 */
SSGEAPI void SSGE_Texture_DestroyName(char *name);

/**
 * Destroy all texture
 */
SSGEAPI void SSGE_Texture_DestroyAll();

#ifdef __cplusplus
}
#endif

#endif // __SSGE_TEXTURE_H__