#ifndef __SSGE_H__
#define __SSGE_H__

#define SSGE_VERSION_MAJOR 2
#define SSGE_VERSION_MINOR 0
#define SSGE_VERSION_PATCH 0

#include <stdbool.h>
#include <stdint.h>

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#include "SSGE/SSGE_texture.h"
#include "SSGE/SSGE_animation.h"
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

/**
 * Initialize the engine
 * \param title The title of the window
 * \param width The window width
 * \param height The window height
 * \param fps The frames per second
 * \return The engine struct
 */
SSGEAPI const SSGE_Engine *SSGE_Init(char *title, uint16_t width, uint16_t height, uint16_t fps);

/**
 * Quit the engine
 * \note This function must be called at the end of the program
 */
SSGEAPI void SSGE_Quit();

/**
 * Run the engine
 * \param update The update function
 * \param draw The draw function
 * \param eventHandler The event handler function
 * \param data The `void *` to pass to the functions (update, draw, eventHandler)
 * \warning The engine runs in an infinite loop until the window is closed
 * \note The order of execution is as follows: Event handling (thread), Update (thread), (Clear screen), Draw
 * \note The `eventHandler` and `update` function is executed on a thread for double buffering. All `SSGE` draw functions should be called in the user `draw` function
 */
SSGEAPI void SSGE_Run(SSGE_UpdateFunc update, SSGE_DrawFunc draw, SSGE_EventHandler eventHandler, void *data);

// Window functions

/**
 * Set the window title
 * \param title The title of the window
 */
SSGEAPI void SSGE_SetWindowTitle(char *title);

/**
 * Set the window icon
 * \param filename The path to the icon
 */
SSGEAPI void SSGE_SetWindowIcon(char *filename);

/**
 * Set the window size
 * \param width The target width
 * \param height The target height
 */
SSGEAPI void SSGE_WindowResize(uint16_t width, uint16_t height);

/**
 * Set the window as resizable
 * \param resizable True if the window should be resizable, false otherwise
 */
SSGEAPI void SSGE_WindowResizable(bool resizable);

/**
 * Set the window as fullscreen
 * \param fullscreen True if the window should be fullscreen, false otherwise
 */
SSGEAPI void SSGE_WindowFullscreen(SSGE_WindowMode fullscreen);

/**
 * Set the max number of frame to skip when frameskipping
 * \param max The max to set
 */
SSGEAPI void SSGE_SetFrameskipMax(uint8_t max);

/**
 * Set VSync state
 * \param vsync If VSync should be enabled or disabled
 */
SSGEAPI void SSGE_SetVSync(bool vsync);

/**
 * Set the manual update mode
 * \param manualUpdate True if the manual update mode should be enabled, false otherwise
 * \warning Use manual update mode ONLY if you know what you are doing.
 * \warning As the engine is threaded and double buffered, you should be carefull of timing and race conditions
 * \note This function should be called before the `SSGE_Run` function
 * \note When the manual update mode is enabled, the screen will only be cleared and updated when the `SSGE_ManualUpdate` function is called.
 * \note Setting the manual update mode may be more efficient when the screen does not need to be updated every frame
 * \note If VSync is enabled, the manual update mode is ignored
 */
SSGEAPI void SSGE_SetManualUpdate(bool manualUpdate);

/**
 * Manually updates the screen
 * \note This function should be called when the manual update mode is enabled
 * \note It does nothing if the manual update mode is disabled
 */
SSGEAPI void SSGE_ManualUpdate();

// Utility functions

/**
 * Set the color of the renderer
 * \param color The color to set
 */
SSGEAPI void SSGE_SetColor(SSGE_Color color);

/**
 * Change the background color
 * \param color The color to set
 */
SSGEAPI void SSGE_SetBackgroundColor(SSGE_Color color);

// Event functions

/**
 * Get the mouse position
 * \param x The variable to store the x coordinate of the mouse
 * \param y The variable to store the y coordinate of the mouse
 */
SSGEAPI void SSGE_GetMousePosition(int *x, int *y);

/**
 * Check if an object is hovered
 * \param object The object to check
 * \return True if the object is hovered, false otherwise
 */
SSGEAPI bool SSGE_ObjectIsHovered(SSGE_Object *object);

/**
 * Get the hovered object
 * \return The hovered object, NULL if no object is hovered
 * \warning If multiple objects are hovered, returns the hovered object with the smallest id
 */
SSGEAPI SSGE_Object *SSGE_GetHoveredObject();

/**
 * Get the list of the objects that are hovered
 * \param objects The array to store the hovered objects
 * \param size The size of the array
 * \return The number of objects retrieved
 */
SSGEAPI uint32_t SSGE_GetHoveredObjects(SSGE_Object *objects[], uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_H__