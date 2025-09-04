#ifndef __SSGE_OBJECT_H__
#define __SSGE_OBJECT_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an object
 * \param id Where to store the id of the object
 * \param name The name of the object
 * \param x The x coordinate of the object
 * \param y The y coordinate of the object
 * \param width The width of the object
 * \param height The height of the object
 * \param hitbox True if the object has an hitbox, false otherwise
 * \param data The data of the object
 * \param destroyData The function to destroy the data of the object
 * \return The object
 * \note The object is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Object *SSGE_Object_Create(uint32_t *id, char *name, int x, int y, int width, int height, bool hitbox, void *data, void (*destroyData)(void *));

/**
 * Instantiate an object from an object template
 * \param id Where to store the id of the object
 * \param template The object template to instantiate
 * \param x The x coordinate of the object
 * \param y The y coordinate of the object
 * \param data The data of the object
 * \return The object
 * \note The object is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Object *SSGE_Object_Instantiate(uint32_t *id, SSGE_ObjectTemplate *template, char *name, int x, int y, void *data);

/**
 * Check if an object exists
 * \param id The id of the object
 * \return True if the object exists, false otherwise
 */
SSGEAPI bool SSGE_Object_Exists(uint32_t id);

/**
 * Check if an object exists
 * \param name The name of the object
 * \return True if the object exists, false otherwise
 */
SSGEAPI bool SSGE_Object_ExistsName(char *name);

/**
 * Move an object
 * \param object The object to move
 * \param x The new x coordinate
 * \param y The new y coordinate
 */
SSGEAPI void SSGE_Object_Move(SSGE_Object *object, int x, int y);

/**
 * Move an object relatively to its current position
 * \param object The object to move
 * \param dx The change in x coordinate
 * \param dy The change in y coordinate
 */
SSGEAPI void SSGE_Object_MoveRel(SSGE_Object *object, int dx, int dy);

/**
 * Bind a texture to an object
 * \param object The object to bind the texture to
 * \param texture The new texture of the object
 */
SSGEAPI void SSGE_Object_BindTexture(SSGE_Object *object, SSGE_Texture *texture);

/**
 * Bind an animation to an object
 * \param object The object to bind the animation to
 * \param animation The new animation of the texture
 */
SSGEAPI void SSGE_Object_BindAnimation(SSGE_Object *object, SSGE_Animation *animation);

/**
 * Remove the texure of an object
 * \param object The object to remove the texture of
 */
SSGEAPI void SSGE_Object_RemoveSprite(SSGE_Object *object);
#define SSGE_Object_RemoveTexture SSGE_Object_RemoveSprite
#define SSGE_Object_RemoveAnim SSGE_Object_RemoveSprite

/**
 * Get an object by id
 * \param id The id of the object
 * \return The object
 */
SSGEAPI SSGE_Object *SSGE_Object_Get(uint32_t id);

/**
 * Get an object by name
 * \param name The name of the object
 * \return The object with the given name
 */
SSGEAPI SSGE_Object *SSGE_Object_GetName(char *name);

/**
 * Get the data of the object
 * \param object The object to get the data of
 */
SSGEAPI void *SSGE_Object_GetData(SSGE_Object *object);

/**
 * Destroy an object by id
 * \param id The id of the object
 */
SSGEAPI void SSGE_Object_Destroy(uint32_t id);

/**
 * Destroy all objects with a given name
 * \param name The name of the object
 */
SSGEAPI void SSGE_Object_DestroyName(char *name);

/**
 * Destroy all objects
 */
SSGEAPI void SSGE_Object_DestroyAll();

/**
 * Check if a hitbox is colliding with another hitbox
 * \param hitbox1 The first hitbox
 * \param hitbox2 The second hitbox
 * \return True if the hitboxes are colliding, false otherwise
 */
SSGEAPI bool SSGE_Object_IsColliding(SSGE_Object *hitbox1, SSGE_Object *hitbox2);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_OBJECT_H__