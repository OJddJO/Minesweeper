#ifndef __SSGE_CONFIG_H__
#define __SSGE_CONFIG_H__

#ifdef DLL_EXPORT
    #define SSGEDECL __declspec(dllexport)
#else
    #define SSGEDECL
#endif

#ifdef SSGE_GET_SDL
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
    #undef SSGE_GET_SDL
#endif

#endif // __SSGE_CONFIG_H__