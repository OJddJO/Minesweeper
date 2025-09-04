#ifndef __SSGE_ANIMATION_H__
#define __SSGE_ANIMATION_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an animation with frames
 * \param id Where to store the id of the animation
 * \param name The name of the animation
 * \param frameCount The number of frames for the animation
 * \param width The width of the frames
 * \param height The height of the frames
 * \return The animation
 */
SSGEAPI SSGE_Animation *SSGE_Animation_CreateFrames(uint32_t *id, char *name, uint32_t frameCount, uint16_t width, uint16_t height);

/**
 * Create an animation with a draw function
 * \param id Where to store the id of the animation
 * \param name The name of the animation
 * \param draw The draw function to call when playing the animation
 * \return The animation
 */
SSGEAPI SSGE_Animation *SSGE_Animation_CreateFunc(uint32_t *id, char *name, void (*draw)(SSGE_AnimationState *));

/**
 * Set the anchor the frames
 * \param animation The animation to set the frames anchor
 * \param x The x coordinate of the anchor
 * \param y The y coordinate of the anchor
 * \note This only works for animation with frames
 * \note Using this function on an animation with a function will throw an error
 */
SSGEAPI void SSGE_Animation_Anchor(SSGE_Animation *animation, int x, int y);

/**
 * Add a frame to an animation
 * \param animation The animation to add the frame to
 * \param frametime The duration of the frame
 * \param file The path to the frame
 * \note This only works for animation with frames
 * \note Using this function on an animation with a function will throw an error
 */
SSGEAPI void SSGE_Animation_AddFrame(SSGE_Animation *animation, uint8_t frametime, char *file);

/**
 * Add a frame from a tilemap to an animation
 * \param animation The animation to add the frame to
 * \param frametime The duration of the frame
 * \param tilemap The tilemap to get the tile used as frame from
 * \param row The row of the tile
 * \param col The column of the tile
 * \note This only works for animation with frames
 * \note Using this function on an animation with a function will throw an error
 */
SSGEAPI void SSGE_Animation_AddFrameTilemap(SSGE_Animation *animation, uint8_t frametime, SSGE_Tilemap *tilemap, int row, int col);

/**
 * Get an animation
 * \param id The id of the animation
 * \return The animation
 */
SSGEAPI SSGE_Animation *SSGE_Animation_Get(uint32_t id);

/**
 * Get an animation by its name
 * \param name The name of the animation
 * \return The animation
 */
SSGEAPI SSGE_Animation *SSGE_Animation_GetName(char *name);

/**
 * Play an animation
 * \param animation The animation to play
 * \param x The x coordinate where to play the animation
 * \param y The y coordinate where to play the animation
 * \param loop The number of time the animation should be played (0 means once, -1 means indefinitly)
 * \param reversed If the animation should be reversed
 * \param pingpong If the animation should pingpong (normal -> reversed)
 * \return The id of the animation state bound to the animation
 */
SSGEAPI uint32_t SSGE_Animation_Play(SSGE_Animation *animation, int x, int y, uint32_t loop, bool reversed, bool pingpong);

/**
 * Pause an animation
 * \param id The id of the animation state bound to the animation to pause
 */
SSGEAPI void SSGE_Animation_Pause(uint32_t id);

/**
 * Resume an animation
 * \param id The id of the animation state bound to the animation to resume
 */
SSGEAPI void SSGE_Animation_Resume(uint32_t id);

/**
 * Stop an animation
 * \param id The id of the animation state bound to the animation to stop
 */
SSGEAPI void SSGE_Animation_Stop(uint32_t id);

/**
 * Move an animation
 * \param id The id of the animation state bound to the animation to move
 */
SSGEAPI void SSGE_Animation_Move(uint32_t id, int x, int y);

/**
 * Update an animation
 * \param id The id of the animation state bound to the animation to update
 */
SSGEAPI void SSGE_Animation_Update(uint32_t id);

/**
 * Update all currently playing animations
 */
SSGEAPI void SSGE_Animation_UpdateAll();

#ifdef __cplusplus
}
#endif

#endif //__SSGE_ANIMATION_H__