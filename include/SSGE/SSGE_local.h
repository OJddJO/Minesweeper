#ifndef __SSGE_LOCAL_H__
#define __SSGE_LOCAL_H__

#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SSGE_Engine *_engine;
extern SSGE_Array *_texture_list;
extern SSGE_Array *_object_list;
extern SSGE_Array *_object_template_list;
extern SSGE_Array *_font_list;
extern SSGE_Array *_audio_list;
extern SSGE_Event _event;
extern SSGE_Color _color;
extern SSGE_Color _clear_color;
extern bool _manual_update_frame;
extern bool _update_frame;

void _assert_engine_init();

void _destroy_texture(void *ptr);
void _destroy_object(void *ptr);
void _destroy_template(void *ptr);
void _destroy_font(void *ptr);
void _destroy_audio(void *ptr);

uint32_t _add_texture_to_list(SSGE_Texture *texture, char *name);
uint32_t _add_object_to_list(SSGE_Object *object, char *name);
uint32_t _add_object_template_to_list(SSGE_ObjectTemplate *template, char *name);
uint32_t _add_audio_to_list(SSGE_Audio *audio, char *name);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_LOCALVAR_H__