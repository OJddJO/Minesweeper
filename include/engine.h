#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2_gfxPrimitives.h"

// Texture structure (SDL_Texture)
#define Texture SDL_Texture
// Color structure {r, g, b, a} (SDL_Color)
#define Color SDL_Color
// Point structure {x, y} (SDL_Point)
#define Point SDL_Point
/**
 * Flip enum (SDL_RendererFlip)
 * \param SDL_FLIP_NONE No flip
 * \param SDL_FLIP_HORIZONTAL Horizontal flip
 * \param SDL_FLIP_VERTICAL Vertical flip
 * \param SDL_FLIP_HORIZONTAL_AND_VERTICAL Horizontal and vertical flip
 */ 
#define Flip SDL_RendererFlip
// Audio structure (Mix_Chunk)
#define Audio Mix_Chunk

// Structure prototypes

// Game structure to contain all the game data
typedef struct _Game Game;

// Engine structures

/**
 * Engine structure
 * \param window The window
 * \param renderer The renderer
 * \param isRunning The running state of the engine
 * \param width The width of the window
 * \param height The height of the window
 * \param fps The frames per second
 */
typedef struct _Engine {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int isRunning;
    int width;
    int height;
    int fps;
} Engine;

/**
 * Object template structure
 * \param texture The filename of the texture
 * \param width The width of the object
 * \param height The height of the object
 * \param hitbox If objects created from this template have a hitbox
 */
typedef struct _ObjectTemplate {
    Texture *texture;
    int width;
    int height;
    bool hitbox;
} ObjectTemplate;

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
typedef struct _Object {
    Texture *texture;
    int x;
    int y;
    int width;
    int height;
    bool hitbox;
    void *data;
} Object;

/**
 * Tilemap structure
 * \param texture The texture of the tilemap
 * \param tile_width The width of the tiles
 * \param tile_height The height of the tiles
 * \param spacing The spacing between the tiles
 * \param nb_rows The number of rows in the tilemap
 * \param nb_cols The number of columns in the tilemap
 */
typedef struct _Tilemap {
    Texture *texture;
    int tile_width;
    int tile_height;
    int spacing;
    int nb_rows;
    int nb_cols;
} Tilemap;

/**
 * Tile structure
 * \param tilemap The tilemap of the tile
 * \param row The row of the tile
 * \param col The column of the tile
 */
typedef struct _Tile {
    Tilemap *tilemap;
    int row;
    int col;
} Tile;

/**
 * Object template list structure
 * \param id The id of the object template list item
 * \param name The name of the object template
 * \param object_template The object template
 * \param next The next object template list item
 */
typedef struct _ObjectTemplateList {
    Uint32 id;
    char *name;
    ObjectTemplate *object_template;
    struct _ObjectTemplateList *next;
} ObjectTemplateList;

/**
 * Object list structure
 * \param id The id of the object list item
 * \param name The name of the object
 * \param object The object
 * \param next The next object list item
 */
typedef struct _ObjectList {
    Uint32 id;
    char *name;
    Object *object;
    struct _ObjectList *next;
} ObjectList;

/**
 * Texture list structure
 * \param id The id of the texture list item
 * \param name The name of the texture
 * \param texture The texture
 * \param next The next texture list item
 */
typedef struct _TextureList {
    Uint32 id;
    char *name;
    Texture *texture;
    struct _TextureList *next;
} TextureList;

/**
 * Audio list structure
 * \param id The id of the audio list item
 * \param name The name of the audio
 * \param audio The audio
 * \param next The next audio list item
 */
typedef struct _Audiolist {
    Uint32 id;
    char *name;
    Mix_Chunk *audio;
    struct _Audiolist *next;
} Audiolist;

/**
 * Font structure
 * \param name The name of the font
 * \param font The font
 * \param next The next font
 */
typedef struct _Font {
    char *name;
    TTF_Font *font;
    struct _Font *next;
} Font;

typedef enum _Anchor {
    NW,
    N,
    NE,
    W,
    CENTER,
    E,
    SW,
    S,
    SE
} Anchor;

/**
 * List structure
 * \param data The data of the list item
 * \param next The next list item
 * \param prev The previous list item
 */
typedef struct _List {
    void *data;
    struct _List *next;
    struct _list *prev;
} List;

// Engine functions

void engine_init(const char *title, int width, int height, int fps);
void engine_quit();
void engine_run(void (*update)(Game *), void (*draw)(Game *), void (*event_handler)(SDL_Event, Game *), Game *game);

// Window functions

void set_window_icon(char *filename);
void window_resizable(bool resizable);
void window_fullscreen(bool fullscreen);
void set_manual_update(bool manual_update);
void manual_update();

// Texture functions

Uint32 create_texture(char *filename, char *name);
Texture *get_texture_by_id(int id);
Texture *get_texture_by_name(char *name);
void draw_texture(Texture *texture, int x, int y, int width, int height);
void draw_texture_ex(Texture *texture, int x, int y, int width, int height, double angle, Point *center, Flip flip);
void draw_texture_from_path(char *filename, int x, int y, int width, int height);
void destroy_texture(char *name);
void destroy_all_textures();
void rotate_texture(char *name, double angle); //need to be tested

// Tilemap functions

Tilemap *create_tilemap(char *filename, int tile_width, int tile_height, int spacing, int nb_rows, int nb_cols);
Tile *get_tile(Tilemap *tilemap, int tile_row, int tile_col);
Uint32 get_tile_as_texture(char *name, Tilemap *tilemap, int tile_row, int tile_col);
void draw_tile(Tile *tile, int x, int y);
void draw_tile_with_size(Tile *tile, int x, int y, int width, int height);
void draw_tile_from_tilemap(Tilemap *tilemap, int tile_row, int tile_col, int x, int y);
void destroy_tile(Tile *tile);
void destroy_tilemap(Tilemap *tilemap);

// Object functions

Uint32 create_object(char *name, Texture *texture, int x, int y, int width, int height, bool hitbox, void *data);
Uint32 instantiate_object(ObjectTemplate *object_template, char *name, int x, int y, void *data);
bool object_exists_by_id(int id);
bool object_exists_by_name(char *name);
void draw_object(Object *object);
void change_object_texture(Object *object, Texture *texture);
Object *get_object_by_id(int id);
Object *get_object_by_name(char *name);
void destroy_object_by_name(char *name);
void destroy_all_objects();

// Object template functions

Uint32 create_object_template(char *name, Texture *texture, int width, int height, bool hitbox);
ObjectTemplate *get_template_by_id(int id);
ObjectTemplate *get_template_by_name(char *name);
void destroy_object_template(char *name);
void destroy_all_templates();

// Hitbox functions

Object *create_hitbox(char *name, int x, int y, int width, int height);
bool hitbox_is_colliding(Object *hitbox1, Object *hitbox2);

// Geometry functions

void draw_line(int x1, int y1, int x2, int y2, Color color);
void draw_rect(int x1, int y1, int x2, int y2, Color color);
void draw_circle(int x, int y, int radius, Color color);
void draw_ellipse(int x, int y, int rx, int ry, Color color);

void draw_line_thick(int x1, int y1, int x2, int y2, Color color, int thickness);
void draw_rect_thick(int x1, int y1, int x2, int y2, Color color, int thickness);
void draw_circle_thick(int x, int y, int radius, Color color, int thickness);
void draw_ellipse_thick(int x, int y, int rx, int ry, Color color, int thickness);

void draw_geometry(Texture *texture, int x, int y);
Uint32 create_line(char *name, int x1, int y1, int x2, int y2, Color color);
Uint32 create_rect(char *name, int x1, int y1, int x2, int y2, Color color);
Uint32 create_circle(char *name, int x, int y, int radius, Color color);
Uint32 create_ellipse(char *name, int x, int y, int rx, int ry, Color color);
Uint32 create_line_thick(char *name, int x1, int y1, int x2, int y2, Color color, int thickness);
Uint32 create_rect_thick(char *name, int x1, int y1, int x2, int y2, Color color, int thickness);
Uint32 create_circle_thick(char *name, int x, int y, int radius, Color color, int thickness);
Uint32 create_ellipse_thick(char *name, int x, int y, int rx, int ry, Color color, int thickness);

// Utility functions

void set_color(Color color);
void set_background_color(Color color);

// Event functions

void get_mouse_position(int *x, int *y);
bool any_key_pressed();
bool object_is_hovered(Object *object);
bool object_is_hovered_by_name(char *name);
void get_hovered_objects(List *objects);

// Text functions

void load_font(char *filename, int size, char *name);
void draw_text(char *font_name, char *text, int x, int y, Color color, Anchor anchor);
void close_font(char *name);
void close_all_fonts();

// Audio functions

Uint32 load_audio(char *filename, char *name);
Audio *get_audio_by_id(int id);
Audio *get_audio_by_name(char *name);
void play_audio(Audio *audio, int channel);
void play_audio_by_name(char *name, int channel);
void pause_audio(int channel);
void stop_audio(int channel);
void close_audio(char *name);
void close_all_audios();

#endif // __ENGINE_H__