#ifndef __SSGE_H__
#define __SSGE_H__

#ifndef SSGEDECL
    #ifdef DLL_EXPORT
        #define SSGEDECL __declspec(dllexport)
    #else
        #define SSGEDECL 
    #endif
#endif // SSGEDECL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SDL2/SDL2_gfxPrimitives.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************
 * SDL Structures
 ************************************************/

// Texture structure (SDL_Texture)
typedef struct SDL_Texture SSGE_Texture;

/**
 * Color structure (SDL_Color)
 * \param r `Uint8` The red component of the color
 * \param g `Uint8` The green component of the color
 * \param b `Uint8` The blue component of the color
 * \param a `Uint8` The alpha component of the color
 */
typedef struct SDL_Color SSGE_Color;

/**
 * Point structure (SDL_Point)
 * \param x `int` The x coordinate of the point
 * \param y `int` The y coordinate of the point
 */
typedef struct SDL_Point SSGE_Point;

/**
 * Flip enum (SDL_RendererFlip)
 * \param SSGE_FLIP_NONE No flip
 * \param SSGE_FLIP_HORIZONTAL Horizontal flip
 * \param SSGE_FLIP_VERTICAL Vertical flip
 * \param SSGE_FLIP_HOR_VER Horizontal and vertical flip
 */
typedef enum {
    SSGE_FLIP_NONE       = 0x00000000,   // no flip
    SSGE_FLIP_HORIZONTAL = 0x00000001,   // flip horizontally
    SSGE_FLIP_VERTICAL   = 0x00000002,   // flip vertically
    SSGE_FLIP_HOR_VER    = 0x00000003    // flip horizontally and vertically
} SSGE_Flip;

// Audio structure (Mix_Chunk)
typedef struct Mix_Chunk SSGE_Audio;

// Event structure (SDL_Event)
typedef union SDL_Event SSGE_Event;


/************************************************
 * Prototypes
 ************************************************/

// Game structure prototype to contain all datas
typedef struct _Game Game;

/*************************************************
 * SSGE Structures
 *************************************************/

/**
 * Engine structure
 * \param window The window
 * \param renderer The renderer
 * \param isRunning The running state of the engine
 * \param width The width of the window
 * \param height The height of the window
 * \param fps The frames per second
 */
typedef struct _SSGE_Engine {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    int width;
    int height;
    int fps;
} SSGE_Engine;

/**
 * Object template structure
 * \param texture The filename of the texture
 * \param width The width of the object
 * \param height The height of the object
 * \param hitbox If objects created from this template have a hitbox
 */
typedef struct _SSGE_ObjectTemplate {
    SSGE_Texture *texture;
    int width;
    int height;
    bool hitbox;
} SSGE_ObjectTemplate;

/**
 * Object structure
 * \param texture The texture of the object
 * \param x The x position of the object
 * \param y The y position of the object
 * \param width The width of the object
 * \param height The height of the object
 * \param hitbox If the object has a hitbox
 * \param data The data of the object
 */
typedef struct _SSGE_Object {
    SSGE_Texture *texture;
    int x;
    int y;
    int width;
    int height;
    bool hitbox;
    void *data;
} SSGE_Object;

/**
 * Tilemap structure
 * \param texture The texture of the tilemap
 * \param tile_width The width of the tiles
 * \param tile_height The height of the tiles
 * \param spacing The spacing between the tiles
 * \param nb_rows The number of rows in the tilemap
 * \param nb_cols The number of columns in the tilemap
 */
typedef struct _SSGE_Tilemap {
    SSGE_Texture *texture;
    int tile_width;
    int tile_height;
    int spacing;
    int nb_rows;
    int nb_cols;
} SSGE_Tilemap;

/**
 * Tile structure
 * \param tilemap The tilemap of the tile
 * \param row The row of the tile
 * \param col The column of the tile
 */
typedef struct _SSGE_Tile {
    SSGE_Tilemap *tilemap;
    int row;
    int col;
} SSGE_Tile;

/**
 * Object template list structure
 * \param id The id of the object template list item
 * \param name The name of the object template
 * \param object_template The object template
 * \param next The next object template list item
 */
typedef struct _SSGE_ObjectTemplateList {
    Uint32 id;
    char *name;
    SSGE_ObjectTemplate *object_template;
    struct _SSGE_ObjectTemplateList *next;
} SSGE_ObjectTemplateList;

/**
 * Object list structure
 * \param id The id of the object list item
 * \param name The name of the object
 * \param object The object
 * \param next The next object list item
 */
typedef struct _SSGE_ObjectList {
    Uint32 id;
    char *name;
    SSGE_Object *object;
    struct _SSGE_ObjectList *next;
} SSGE_ObjectList;

/**
 * Texture list structure
 * \param id The id of the texture list item
 * \param name The name of the texture
 * \param texture The texture
 * \param next The next texture list item
 */
typedef struct _SSGE_TextureList {
    Uint32 id;
    char *name;
    SSGE_Texture *texture;
    struct _SSGE_TextureList *next;
} SSGE_TextureList;

/**
 * Audio list structure
 * \param id The id of the audio list item
 * \param name The name of the audio
 * \param audio The audio
 * \param next The next audio list item
 */
typedef struct _SSGE_Audiolist {
    Uint32 id;
    char *name;
    Mix_Chunk *audio;
    struct _SSGE_Audiolist *next;
} SSGE_Audiolist;

/**
 * Font structure
 * \param name The name of the font
 * \param font The font
 * \param next The next font
 */
typedef struct _SSGE_Font {
    char *name;
    TTF_Font *font;
    struct _SSGE_Font *next;
} SSGE_Font;

typedef enum _SSGE_Anchor {
    NW,
    N,
    NE,
    W,
    CENTER,
    E,
    SW,
    S,
    SE
} SSGE_Anchor;

/************************************************
 * SSGE Functions
 ************************************************/

SSGEDECL void SSGE_engine_init(const char *title, int width, int height, int fps);
SSGEDECL void SSGE_engine_quit();
SSGEDECL void SSGE_engine_run(void (*update)(Game *), void (*draw)(Game *), void (*event_handler)(SDL_Event, Game *), Game *game);

// Window functions

SSGEDECL void SSGE_set_window_title(char *title);
SSGEDECL void SSGE_set_window_icon(char *filename);
SSGEDECL void SSGE_window_resizable(bool resizable);
SSGEDECL void SSGE_window_fullscreen(bool fullscreen);
SSGEDECL void SSGE_set_manual_update(bool manual_update);
SSGEDECL void SSGE_manual_update();

// Texture functions

SSGEDECL Uint32 SSGE_load_texture(char *filename, char *name);
SSGEDECL SSGE_Texture *SSGE_get_texture(Uint32 id);
SSGEDECL SSGE_Texture *SSGE_get_texture_by_name(char *name);
SSGEDECL void SSGE_draw_texture(SSGE_Texture *texture, int x, int y, int width, int height);
SSGEDECL void SSGE_draw_texture_ex(SSGE_Texture *texture, int x, int y, int width, int height, double angle, SSGE_Point *center, SSGE_Flip flip);
SSGEDECL void SSGE_draw_texture_from_path(char *filename, int x, int y, int width, int height);
SSGEDECL void SSGE_destroy_texture(Uint32 id);
SSGEDECL void SSGE_destroy_texture_by_name(char *name);
SSGEDECL void SSGE_destroy_all_textures();

// Tilemap functions

SSGEDECL SSGE_Tilemap *SSGE_load_tilemap(char *filename, int tile_width, int tile_height, int spacing, int nb_rows, int nb_cols);
SSGEDECL SSGE_Tile *SSGE_get_tile(SSGE_Tilemap *tilemap, int tile_row, int tile_col);
SSGEDECL Uint32 SSGE_get_tile_as_texture(char *name, SSGE_Tilemap *tilemap, int tile_row, int tile_col);
SSGEDECL void SSGE_draw_tile(SSGE_Tile *tile, int x, int y);
SSGEDECL void SSGE_draw_tile_with_size(SSGE_Tile *tile, int x, int y, int width, int height);
SSGEDECL void SSGE_draw_tile_from_tilemap(SSGE_Tilemap *tilemap, int tile_row, int tile_col, int x, int y);
SSGEDECL void SSGE_destroy_tile(SSGE_Tile *tile);
SSGEDECL void SSGE_destroy_tilemap(SSGE_Tilemap *tilemap);

// Object functions

SSGEDECL Uint32 SSGE_create_object(char *name, SSGE_Texture *texture, int x, int y, int width, int height, bool hitbox, void *data);
SSGEDECL Uint32 SSGE_instantiate_object(SSGE_ObjectTemplate *object_template, char *name, int x, int y, void *data);
SSGEDECL bool SSGE_object_exists(Uint32 id);
SSGEDECL bool SSGE_object_exists_by_name(char *name);
SSGEDECL void SSGE_draw_object(SSGE_Object *object);
SSGEDECL void SSGE_change_object_texture(SSGE_Object *object, SSGE_Texture *texture);
SSGEDECL SSGE_Object *SSGE_get_object(Uint32 id);
SSGEDECL SSGE_Object *SSGE_get_object_by_name(char *name);
SSGEDECL void SSGE_destroy_object(Uint32 id);
SSGEDECL void SSGE_destroy_object_by_name(char *name);
SSGEDECL void SSGE_destroy_all_objects();

// Object template functions

SSGEDECL Uint32 SSGE_create_object_template(char *name, SSGE_Texture *texture, int width, int height, bool hitbox);
SSGEDECL SSGE_ObjectTemplate *SSGE_get_template(Uint32 id);
SSGEDECL SSGE_ObjectTemplate *SSGE_get_template_by_name(char *name);
SSGEDECL void SSGE_destroy_object_template(Uint32 id);
SSGEDECL void SSGE_destroy_object_template_by_name(char *name);
SSGEDECL void SSGE_destroy_all_templates();

// Hitbox functions

SSGEDECL Uint32 SSGE_create_hitbox(char *name, int x, int y, int width, int height);
SSGEDECL bool SSGE_hitbox_is_colliding(SSGE_Object *hitbox1, SSGE_Object *hitbox2);

// Geometry functions

SSGEDECL void SSGE_draw_line(int x1, int y1, int x2, int y2, SSGE_Color color);
SSGEDECL void SSGE_draw_rect(int x1, int y1, int x2, int y2, SSGE_Color color);
SSGEDECL void SSGE_draw_circle(int x, int y, int radius, SSGE_Color color);
SSGEDECL void SSGE_draw_ellipse(int x, int y, int rx, int ry, SSGE_Color color);

SSGEDECL void SSGE_draw_line_thick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);
SSGEDECL void SSGE_draw_rect_thick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);
SSGEDECL void SSGE_draw_circle_thick(int x, int y, int radius, SSGE_Color color, int thickness);
SSGEDECL void SSGE_draw_ellipse_thick(int x, int y, int rx, int ry, SSGE_Color color, int thickness);

SSGEDECL void SSGE_fill_rect(int x1, int y1, int x2, int y2, SSGE_Color color);
SSGEDECL void SSGE_fill_circle(int x, int y, int radius, SSGE_Color color);
SSGEDECL void SSGE_fill_ellipse(int x, int y, int rx, int ry, SSGE_Color color);

SSGEDECL void SSGE_draw_geometry(SSGE_Texture *texture, int x, int y);

SSGEDECL Uint32 SSGE_create_line(char *name, int x1, int y1, int x2, int y2, SSGE_Color color);
SSGEDECL Uint32 SSGE_create_rect(char *name, int x1, int y1, int x2, int y2, SSGE_Color color);
SSGEDECL Uint32 SSGE_create_circle(char *name, int x, int y, int radius, SSGE_Color color);
SSGEDECL Uint32 SSGE_create_ellipse(char *name, int x, int y, int rx, int ry, SSGE_Color color);

SSGEDECL Uint32 SSGE_create_line_thick(char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);
SSGEDECL Uint32 SSGE_create_rect_thick(char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);
SSGEDECL Uint32 SSGE_create_circle_thick(char *name, int x, int y, int radius, SSGE_Color color, int thickness);
SSGEDECL Uint32 SSGE_create_ellipse_thick(char *name, int x, int y, int rx, int ry, SSGE_Color color, int thickness);

// Utility functions

SSGEDECL void SSGE_set_color(SSGE_Color color);
SSGEDECL void SSGE_set_background_color(SSGE_Color color);

// Event functions

SSGEDECL void SSGE_get_mouse_position(int *x, int *y);
SSGEDECL bool SSGE_any_key_pressed();
SSGEDECL bool SSGE_object_is_hovered(SSGE_Object *object);
SSGEDECL bool SSGE_object_is_hovered_by_name(char *name);
SSGEDECL void SSGE_get_hovered_objects(SSGE_Object *objects[], int size);
SSGEDECL void SSGE_get_hovered_objects_ids(Uint32 ids[], int size);

// Text functions

SSGEDECL void SSGE_load_font(char *filename, int size, char *name);
SSGEDECL void SSGE_draw_text(char *font_name, char *text, int x, int y, SSGE_Color color, SSGE_Anchor anchor);
SSGEDECL Uint32 SSGE_create_text_as_texture(char *font_name, char *text, SSGE_Color color, char *texture_name);
SSGEDECL void SSGE_close_font(char *name);
SSGEDECL void SSGE_close_all_fonts();

// Audio functions

SSGEDECL Uint32 SSGE_load_audio(char *filename, char *name);
SSGEDECL SSGE_Audio *SSGE_get_audio(Uint32 id);
SSGEDECL SSGE_Audio *SSGE_get_audio_by_name(char *name);
SSGEDECL void SSGE_play_audio(SSGE_Audio *audio, int channel);
SSGEDECL void SSGE_play_audio_by_name(char *name, int channel);
SSGEDECL void SSGE_pause_audio(int channel);
SSGEDECL void SSGE_stop_audio(int channel);
SSGEDECL void SSGE_close_audio(Uint32 id);
SSGEDECL void SSGE_close_audio_by_name(char *name);
SSGEDECL void SSGE_close_all_audios();

#ifdef __cplusplus
}
#endif

#endif // __SSGE_H__