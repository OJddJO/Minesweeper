#ifndef __SSGE_AUDIO_H__
#define __SSGE_AUDIO_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Loads an audio
 * \param filename The path to the audio
 * \param name The name of the audio
 * \return The audio
 */
SSGEDECL uint32_t SSGE_LoadAudio(char *filename, char *name);

/**
 * Plays an audio by id
 * \param id The id of the audio
 * \param channel The channel to play the audio on, -1 for first free channel. Channels must be a number between 0 and 3
 */
SSGEDECL void SSGE_PlayAudio(uint32_t id, int channel);

/**
 * Plays an audio by name
 * \param name The name of the audio
 * \param channel The channel to play the audio on, -1 for first free channel. Channels must be a number between 0 and 3
 */
SSGEDECL void SSGE_PlayAudioByName(char *name, int channel);

/**
 * Resume an audio
 * \param channel The channel to resume the audio on, -1 for all
 */
SSGEDECL void SSGE_ResumeAudio(int channel);

/**
 * Pauses an audio
 * \param channel The channel to pause the audio on, -1 for all
 */
SSGEDECL void SSGE_PauseAudio(int channel);

/**
 * Stops an audio
 * \param channel The channel to stop the audio on, -1 for all
 */
SSGEDECL void SSGE_StopAudio(int channel);

/**
 * Closes an audio by id
 * \param id The id of the audio
 */
SSGEDECL void SSGE_CloseAudio(uint32_t id);

/**
 * Closes an audio by name
 * \param name The name of the audio
 */
SSGEDECL void SSGE_CloseAudioByName(char *name);

/**
 * Closes all audios
 */
SSGEDECL void SSGE_CloseAllAudios();

#ifdef __cplusplus
}
#endif

#endif // __SSGE_AUDIO_H__