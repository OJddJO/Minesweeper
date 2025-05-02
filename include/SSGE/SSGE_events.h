/* This header file essentially remap all SDL_Event, for more information see SDL_events.h*/

#ifndef __SSGE_EVENTS_H__
#define __SSGE_EVENTS_H__

#include <stdint.h>

typedef enum _SSGE_EventType {
    SSGE_FIRSTEVENT         = 0, // UNUSED
    // Application events
    SSGE_QUIT               = 0x100,
    // Window events
    SSGE_WINDOWEVENT        = 0x200,
    // Keyboard events
    SSGE_KEYDOWN            = 0x300,
    SSGE_KEYUP,
    // Mouse events
    SSGE_MOUSEMOTION        = 0x400,
    SSGE_MOUSEBUTTONDOWN,
    SSGE_MOUSEBUTTONUP,
    SSGE_MOUSEWHEEL,
} SSGE_EventType;

typedef struct _SSGE_CommonEvent {
    uint32_t type;
    uint32_t timestamp;
} SSGE_CommonEvent;

enum _SSGE_WindowEventID { // See SDL_video.h
    SSGE_WINDOWEVENT_NONE           = 0,    // UNUSED
    SSGE_WINDOWEVENT_SHOWN,                 // Window has been shown
    SSGE_WINDOWEVENT_HIDDEN,                // Window has been hidden
    SSGE_WINDOWEVENT_EXPOSED,               // Window has been exposed and should be redraw
    SSGE_WINDOWEVENT_MOVED,                 // Window has been moved to (data1, data2)
    SSGE_WINDOWEVENT_RESIZED,               // Window has been resized to data1 x data2
    SSGE_WINDOWEVENT_SIZE_CHANGED,          // Window has been resized by an internal function call
    SSGE_WINDOWEVENT_MINIMIZED,             // Window has been minimized
    SSGE_WINDOWEVENT_MAXIMIZED,             // Window has been maximized
    SSGE_WINDOWEVENT_ENTER          = 10,   // Window has gained mouse focus
    SSGE_WINDOWEVENT_LEAVE,                 // Window has lost mouse focus
    SSGE_WINDOWEVENT_FOCUS_GAINED,          // Window has gained keyboard focus
    SSGE_WINDOWEVENT_FOCUS_LOST,            // Window has lost keyboard focus
    SSGE_WINDOWEVENT_DISPLAY_CHANGED = 18,  // Window has been moved to display data1
};

/**
 * \param event The window event subtype `SSGE_WindowEventID`
 * \param data1 First data, usage depends on the window event
 * \param data2 Second data, usage depends on the window event
 */
typedef struct _SSGE_WindowEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint8_t event;
    uint8_t padding1;
    uint8_t padding2;
    uint8_t padding3;
    int32_t data1;
    int32_t data2;
} SSGE_WindowEvent;

enum _SSGE_Keymod {
    SSGE_KMOD_NONE   = 0x0000,
    SSGE_KMOD_LSHIFT = 0x0001,
    SSGE_KMOD_RSHIFT = 0x0002,
    SSGE_KMOD_LCTRL  = 0x0040,
    SSGE_KMOD_RCTRL  = 0x0080,
    SSGE_KMOD_LALT   = 0x0100,
    SSGE_KMOD_RALT   = 0x0200,
    SSGE_KMOD_LGUI   = 0x0400,
    SSGE_KMOD_RGUI   = 0x0800,
    SSGE_KMOD_NUM    = 0x1000,
    SSGE_KMOD_CAPS   = 0x2000,
    SSGE_KMOD_MODE   = 0x4000,
    SSGE_KMOD_SCROLL = 0x8000,

    SSGE_KMOD_CTRL   = SSGE_KMOD_LCTRL | SSGE_KMOD_RCTRL,
    SSGE_KMOD_SHIFT  = SSGE_KMOD_LSHIFT | SSGE_KMOD_RSHIFT,
    SSGE_KMOD_ALT    = SSGE_KMOD_LALT | SSGE_KMOD_RALT,
    SSGE_KMOD_GUI    = SSGE_KMOD_LGUI | SSGE_KMOD_RGUI,
};

/**
 * \param scancode Physical code of the button
 * \param sym Virtual code of the button (Depends on the keyboard layout)
 * \param mod Current modifiers, see `SSGE_Keymod`
 */
typedef struct _SSGE_Keysym {
    uint32_t scancode;
    int32_t sym;
    uint16_t mod;
    uint32_t unused;
} SSGE_Keysym;

/**
 * \param state 0 if released, 1 if pressed
 * \param repeat Non-zero if this is a key repeat (long press)
 * \param keysym The key pressed, see `SSGE_Keysym`
 */
typedef struct _SSGE_KeyboardEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint8_t state;
    uint8_t repeat;
    uint8_t padding2;
    uint8_t padding3;
    SSGE_Keysym keysym;
} SSGE_KeyboardEvent;

enum _SSGE_Mouse {
    SSGE_MOUSE_LEFT = 1,
    SSGE_MOUSE_MIDDLE,
    SSGE_MOUSE_RIGHT,
};

/**
 * \param state 0b001 if left button, 0b010 if middle button, 0b100 if right button
 * \param x X coordinate, relative to the window
 * \param y Y coordinate, relative to the window
 * \param xrel The difference between the previous X pos and current X pos
 * \param yrel The difference between the previous Y pos and current Y pos
 */
typedef struct _SSGE_MouseMotionEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    uint32_t state;
    int32_t x;
    int32_t y;
    int32_t xrel;
    int32_t yrel;
} SSGE_MouseMotionEvent;

/**
 * \param button 1 = left, 2 = middle, 3 = right
 * \param state 0 = released, 1 = pressed
 * \param clicks 1 for single-click, 2 for double-click, etc
 * \param x X coordinate, relative to the window
 * \param y Y coordinate, relative to the window
 */
typedef struct _SSGE_MouseButtonEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    int8_t button;
    int8_t state;
    int8_t clicks;
    int8_t padding1;
    int32_t x;
    int32_t y;
} SSGE_MouseButtonEvent;

/**
 * \param x The amount scrolled horizontally
 * \param y The amount scrolled vertically
 * \param direction The direction of the scroll, 0 if normal, 1 if flipped/natural scroll
 * \param preciseX The amount scrolled horizontally in float
 * \param preciseY The amount scrolled vertically in float
 * \param mouseX The X coordinate of the mouse, relative to the window
 * \param mouseY The Y coordinate of the mouse, relative to the window
 */
typedef struct _SSGE_MouseWheelEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    int32_t x;
    int32_t y;
    uint32_t direction; // 0 if normal, 1 if flipped/natural
    float preciseX;
    float preciseY;
    int32_t mouseX;
    int32_t mouseY;
} SSGE_MouseWheelEvent;

typedef struct _SSGE_QuitEvent {
    uint32_t type;
    uint32_t timestamp;
} SSGE_QuitEvent;

typedef union _SSGE_Event {
    uint32_t type;
    SSGE_CommonEvent common;
    SSGE_WindowEvent window;
    SSGE_KeyboardEvent key;
    SSGE_MouseMotionEvent motion;
    SSGE_MouseButtonEvent button;
    SSGE_MouseWheelEvent wheel;
    SSGE_QuitEvent quit;
    uint8_t padding[sizeof(void *) <= 8 ? 56 : sizeof(void *) == 16 ? 64 : 3 * sizeof(void *)];
} SSGE_Event;

#endif //__SSGE_EVENTS_H__