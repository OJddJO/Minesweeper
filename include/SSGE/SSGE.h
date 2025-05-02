#ifndef __SSGE_H__
#define __SSGE_H__

#include <stdbool.h>
#include <stdint.h>

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#include "SSGE/SSGE_texture.h"
#include "SSGE/SSGE_tilemap.h"
#include "SSGE/SSGE_object.h"
#include "SSGE/SSGE_objtemplate.h"
#include "SSGE/SSGE_geometry.h"
#include "SSGE/SSGE_text.h"
#include "SSGE/SSGE_audio.h"
#include "SSGE/SSGE_keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************
 * SSGE Functions
 ************************************************/

/**
 * Initializes the engine
 * \param title The title of the window
 * \param width The width of the window
 * \param height The height of the window
 * \param fps The frames per second
 */
SSGEDECL void SSGE_Init(char *title, int width, int height, int fps);

/**
 * Quits the engine
 * \note This function must be called at the end of the program
 */
SSGEDECL void SSGE_Quit();

/**
 * Runs the engine
 * \param update The update function. Should take a `Game *` as argument and return `void`
 * \param draw The draw function. Should takes a `Game *` as argument and returns `void`
 * \param eventHandler The event handler function. Should takes a `SSGE_Event` and a `Game *` as arguments and returns `void`
 * \param data The `Game *` to pass to the functions (update, draw, eventHandler)
 * \warning The engine runs in an infinite loop until the window is closed
 * \note The order of execution is as follows: Event handling, Update, (Clear screen), Draw
 */
SSGEDECL void SSGE_Run(void (*update)(Game *), void (*draw)(Game *), void (*eventHandler)(SSGE_Event, Game *), Game *data);

// Window functions

/**
 * Sets the window title
 * \param title The title of the window
 */
SSGEDECL void SSGE_SetWindowTitle(char *title);

/**
 * Sets the window icon
 * \param filename The path to the icon
 */
SSGEDECL void SSGE_SetWindowIcon(char *filename);

/**
 * Sets the window as resizable
 * \param resizable True if the window should be resizable, false otherwise
 */
SSGEDECL void SSGE_WindowResizable(bool resizable);

/**
 * Sets the window as fullscreen
 * \param fullscreen True if the window should be fullscreen, false otherwise
 */
SSGEDECL void SSGE_WindowFullscreen(bool fullscreen);

/**
 * Sets the manual update mode
 * \param manualUpdate True if the manual update mode should be enabled, false otherwise
 * \note This function should be called before the `SSGE_Run` function
 * \note When the manual update mode is enabled, the screen will only be cleared and updated when the `SSGE_ManualUpdate` function is called.
 * \note Setting the manual update mode may be more efficient when the screen does not need to be updated every frame
 */
SSGEDECL void SSGE_SetManualUpdate(bool manualUpdate);

/**
 * Manually updates the screen
 * \note This function should be called when the manual update mode is enabled
 * \note It does nothing if the manual update mode is disabled
 */
SSGEDECL void SSGE_ManualUpdate();

// Utility functions

/**
 * Sets the color of the renderer
 * \param color The color to set
 */
SSGEDECL void SSGE_SetColor(SSGE_Color color);

/**
 * Change the background color
 * \param color The color to set
 */
SSGEDECL void SSGE_SetBackgroundColor(SSGE_Color color);

// Event functions

/**
 * Get the mouse position
 * \param x The variable to store the x position of the mouse
 * \param y The variable to store the y position of the mouse
 */
SSGEDECL void SSGE_GetMousePosition(int *x, int *y);

/**
 * Checks if an object is hovered
 * \param object The object to check
 * \return True if the object is hovered, false otherwise
 */
SSGEDECL bool SSGE_ObjectIsHovered(SSGE_Object *object);

/**
 * Get the hovered object
 * \return The hovered object, NULL if no object is hovered
 * \warning If multiple objects are hovered, returns the hovered object with the smallest id
 */
SSGEDECL SSGE_Object *SSGE_GetHoveredObject();

/**
 * Get the list of the objects that are hovered
 * \param objects The array to store the hovered objects
 * \param size The size of the array
 * \return The number of objects retrieved
 */
SSGEDECL uint32_t SSGE_GetHoveredObjects(SSGE_Object *objects[], uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_H__