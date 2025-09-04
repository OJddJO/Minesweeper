#ifndef __SSGE_TEXT_H__
#define __SSGE_TEXT_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load a font
 * \param filename The path to the font
 * \param size The size of the font
 * \param name The name of the font
 */
SSGEAPI void SSGE_Font_Create(char *filename, int size, char *name);

/**
 * Close a font by name
 * \param fontName The name of the font
 */
SSGEAPI void SSGE_Font_Close(char *name);

/**
 * Close all fonts
 */
SSGEAPI void SSGE_Font_CloseAll();

/**
 * Draw text
 * \param fontName The name of the font
 * \param text The text to draw
 * \param x The x coordinate to draw the text
 * \param y The y coordinate to draw the text
 * \param color The color of the text
 * \param anchor The anchor of the text
 */
SSGEAPI void SSGE_Text_Draw(char *fontName, char *text, int x, int y, SSGE_Color color, SSGE_Anchor anchor);

/**
 * Create text as a texture
 * \param id Where to store the texture
 * \param fontName The name of the font
 * \param text The text to draw
 * \param color The color of the text
 * \param textureName The name of the texture
 * \return The poitner of the texture
 * \note The texture is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Texture *SSGE_Text_Create(uint32_t *id, char *fontName, char *text, SSGE_Color color, char *textureName);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_TEXT_H__