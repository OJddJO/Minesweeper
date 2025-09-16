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
 * \return The object
 * \note The object is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Object *SSGE_Object_Create(uint32_t *id, char *name, int x, int y, int width, int height, bool hitbox);

/**
 * Instantiate an object from an object template
 * \param id Where to store the id of the object
 * \param template The object template to instantiate
 * \param x The x coordinate of the object
 * \param y The y coordinate of the object
 * \return The object
 * \note The object is stored internally and can be accessed by its name or its id
 */
SSGEAPI SSGE_Object *SSGE_Object_Instantiate(uint32_t *id, SSGE_ObjectTemplate *template, char *name, int x, int y);

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
 * Bind some data to an object
 * \param object The object to bind the data to
 * \param data The data of the object
 * \param destroy The function to call to destroy the data
 */
SSGEAPI void SSGE_Object_BindData(SSGE_Object *object, void *data, SSGE_DestroyData destroy);

/**
 * Remove the data bound to the object
 * \param object The object to remove the data from
 */
SSGEAPI void SSGE_Object_RemoveData(SSGE_Object *object);

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
 * Resize an object
 * \param object The object to resize
 * \param width The target width
 * \param height The target height
 */
SSGEAPI void SSGE_Object_Resize(SSGE_Object *object, uint16_t width, uint16_t height);

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

/**
 * Check if an object is hovered
 * \param object The object to check
 * \return True if the object is hovered, false otherwise
 */
SSGEAPI bool SSGE_Object_IsHovered(SSGE_Object *object);

/**
 * Get the object at a coordinate
 * \param x The x coordinate to check
 * \param y The y coordinate to check
 * \return The object at the coordinate, NULL if no object is at the coordinate
 * \note An object is considered at a certain coordinate if at least one pixel is at that said coordinate.
 * \note Meaning that it doesn't need to be exactly at that coordinate (doesn't need `object.x == x && object.y == y`).
 * \warning If multiple objects are detected, returns the object with the smallest id
 */
SSGEAPI SSGE_Object *SSGE_Object_GetAt(int x, int y);

/**
 * Get the list of objects at a coordinate
 * \param x The x coordinate to check
 * \param y The y coordinate to check
 * \return The object at the coordinate, NULL if no object is at the coordinate
 * \note An object is considered at a certain coordinate if at least one pixel is at that said coordinate.
 * \note Meaning that it doesn't need to be exactly at that coordinate (doesn't need `object.x == x && object.y == y`).
 */
SSGEAPI uint32_t SSGE_Object_GetAtList(int x, int y, SSGE_Object *objects[], uint32_t size);

/**
 * Get the hovered object
 * \return The hovered object, NULL if no object is hovered
 * \warning If multiple objects are hovered, returns the hovered object with the smallest id
 * \warning It is not recommended to use this to get object at click position, use the event `x` and `y` with the `SSGE_Object_GetAt` function.
 */
SSGEAPI SSGE_Object *SSGE_Object_GetHovered();

/**
 * Get the list of the objects that are hovered
 * \param objects The array to store the hovered objects
 * \param size The size of the array
 * \return The number of objects retrieved
 * \warning It is not recommended to use this to get object at click position, use the event `x` and `y` with the `SSGE_Object_GetAtList` function.
 */
SSGEAPI uint32_t SSGE_Objects_GetHoveredList(SSGE_Object *objects[], uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_OBJECT_H__