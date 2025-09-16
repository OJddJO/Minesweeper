#ifndef __SSGE_OBJTEMPLATE_H__
#define __SSGE_OBJTEMPLATE_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an object template
 * \param id Where to store the id of the object template
 * \param name The name of the object template
 * \param width The width of the object template
 * \param height The height of the object template
 * \param hitbox True if objects created from this template have a hitbox, false otherwise
 * \return The object template
 * \note The object template is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_ObjectTemplate *SSGE_Template_Create(uint32_t *id, char *name, uint16_t width, uint16_t height, bool hitbox);

/**
 * Create an object template with a texture
 * \param id Where to store the id of the object template
 * \param name The name of the object template
 * \param texture The texture of the object template
 * \param width The width of the object template
 * \param height The height of the object template
 * \param hitbox True if objects created from this template have a hitbox, false otherwise
 * \return The object template
 * \note The object template is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_ObjectTemplate *SSGE_Template_CreateStatic(uint32_t *id, char *name, SSGE_Texture *texture, uint16_t width, uint16_t height, bool hitbox);

/**
 * Create an object template with an animation
 * \param id Where to store the id of the object template
 * \param name The name of the object template
 * \param animation The animation of the object template
 * \param width The width of the object template
 * \param height The height of the object template
 * \param hitbox True if objects created from this template have a hitbox, false otherwise
 * \return The object template
 * \note The object template is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_ObjectTemplate *SSGE_Template_CreateAnim(uint32_t *id, char *name, SSGE_Animation *animation, uint16_t width, uint16_t height, bool hitbox);

/**
 * Get an object template by id
 * \param id The id of the object template
 * \return The object template
 */
SSGEAPI SSGE_ObjectTemplate *SSGE_Template_Get(uint32_t id);

/**
 * Get an object template by name
 * \param name The name of the object template
 * \return The object template
 */
SSGEAPI SSGE_ObjectTemplate *SSGE_Template_GetName(char *name);

/**
 * Destroy an object template by id
 * \param id The id of the object template
 */
SSGEAPI void SSGE_Template_Destroy(uint32_t id);

/**
 * Destroy an object template by name
 * \param name The name of the object template
 */
SSGEAPI void SSGE_Template_DestroyName(char *name);

/**
 * Destroy all object templates
 */
SSGEAPI void SSGE_Template_DestroyAll();

#ifdef __cplusplus
}
#endif

#endif // __SSGE_OBJTEMPLATE_H__