#ifndef _VGLINS_RETRO_DISPLAY_LIB_H_
#define _VGLINS_RETRO_DISPLAY_LIB_H_

#include <stdbool.h>
#include <stdint.h>

#ifndef _UINT_ALIASES_
#define _UINT_ALIASES_

typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

#endif

#define VRDL_DEFAULT_RESOLUTION_WIDTH  256
#define VRDL_DEFAULT_RESOLUTION_HEIGHT 240
#define VRDL_DEFAULT_HBLANK            24
#define VRDL_DEFAULT_VBLANK            16

typedef uint32_t vrdl_color;

#define vrdl_color_rgb(r, g, b) (vrdl_color)(((byte)(r) << 24) + ((byte)(g) << 16) + ((byte)(b) << 8) + 0xff)
#define vrdl_color_rgba(r, g, b, a) (vrdl_color)(((byte)(r) << 24) + ((byte)(g) << 16) + ((byte)(b) << 8) + (byte)(a))

typedef enum {
    VRDL_DISPLAY_TYPE_CRT,
    VRDL_DISPLAY_TYPE_LCD
} vrdl_display_type;

typedef enum {
    VRDLK_A = 4,
    VRDLK_B = 5,
    VRDLK_C = 6,
    VRDLK_D = 7,
    VRDLK_E = 8,
    VRDLK_F = 9,
    VRDLK_G = 10,
    VRDLK_H = 11,
    VRDLK_I = 12,
    VRDLK_J = 13,
    VRDLK_K = 14,
    VRDLK_L = 15,
    VRDLK_M = 16,
    VRDLK_N = 17,
    VRDLK_O = 18,
    VRDLK_P = 19,
    VRDLK_Q = 20,
    VRDLK_R = 21,
    VRDLK_S = 22,
    VRDLK_T = 23,
    VRDLK_U = 24,
    VRDLK_V = 25,
    VRDLK_W = 26,
    VRDLK_X = 27,
    VRDLK_Y = 28,
    VRDLK_Z = 29,

    VRDLK_1 = 30,
    VRDLK_2 = 31,
    VRDLK_3 = 32,
    VRDLK_4 = 33,
    VRDLK_5 = 34,
    VRDLK_6 = 35,
    VRDLK_7 = 36,
    VRDLK_8 = 37,
    VRDLK_9 = 38,
    VRDLK_0 = 39,

    VRDLK_RETURN    = 40,
    VRDLK_ESCAPE    = 41,
    VRDLK_BACKSPACE = 42,
    VRDLK_TAB       = 43,
    VRDLK_SPACE     = 44,

    VRDLK_MINUS         = 45,
    VRDLK_EQUALS        = 46,
    VRDLK_LEFT_BRACKET  = 47,
    VRDLK_RIGHT_BRACKET = 48,
    VRDLK_BACKSLASH     = 49,
    VRDLK_NONUSHASH     = 50,
    VRDLK_SEMICOLON     = 51,
    VRDLK_APOSTROPHE    = 52,
    VRDLK_GRAVE         = 53,
    VRDLK_COMMA         = 54,
    VRDLK_PERIOD        = 55,
    VRDLK_SLASH         = 56,

    VRDLK_CAPS_LOCK = 57,

    VRDLK_F1  = 58,
    VRDLK_F2  = 59,
    VRDLK_F3  = 60,
    VRDLK_F4  = 61,
    VRDLK_F5  = 62,
    VRDLK_F6  = 63,
    VRDLK_F7  = 64,
    VRDLK_F8  = 65,
    VRDLK_F9  = 66,
    VRDLK_F10 = 67,
    VRDLK_F11 = 68,
    VRDLK_F12 = 69,

    VRDLK_PRINT_SCREEN = 70,
    VRDLK_SCROLL_LOCK  = 71,
    VRDLK_PAUSE        = 72,
    VRDLK_INSERT       = 73,
    VRDLK_HOME         = 74,
    VRDLK_PAGE_UP      = 75,
    VRDLK_DELETE       = 76,
    VRDLK_END          = 77,
    VRDLK_PAGE_DOWN    = 78,

    VRDLK_RIGHT = 79,
    VRDLK_LEFT  = 80,
    VRDLK_DOWN  = 81,
    VRDLK_UP    = 82,

    VRDLK_NUMLOCK     = 83,
    VRDLK_CLEAR       = 83,
    VRDLK_KP_DIVIDE   = 84,
    VRDLK_KP_MULTIPLY = 85,
    VRDLK_KP_MINUS    = 86,
    VRDLK_KP_PLUS     = 87,
    VRDLK_KP_ENTER    = 88,
    VRDLK_KP_1        = 89,
    VRDLK_KP_2        = 90,
    VRDLK_KP_3        = 91,
    VRDLK_KP_4        = 92,
    VRDLK_KP_5        = 93,
    VRDLK_KP_6        = 94,
    VRDLK_KP_7        = 95,
    VRDLK_KP_8        = 96,
    VRDLK_KP_9        = 97,
    VRDLK_KP_0        = 98,
    VRDLK_KP_PERIOD   = 99,

    VRDLK_LCTRL  = 224,
    VRDLK_LSHIFT = 225,
    VRDLK_LALT   = 226,
    VRDLK_LGUI   = 227,
    VRDLK_RCTRL  = 228,
    VRDLK_RSHIFT = 229,
    VRDLK_RALT   = 230,
    VRDLK_RGUI   = 231
} vrdl_key;

extern bool vrdl_turn_on(int width, int height, vrdl_display_type display_type);
extern void vrdl_turn_off(void);

extern bool vrdl_set_resolution(uint32_t width, uint32_t height);
extern bool vrdl_set_blanking(uint32_t hblank, uint32_t vblank);
extern bool vrdl_set_resolution_and_blanking(uint32_t width, uint32_t height, uint32_t hblank, uint32_t vblank);

extern bool vrdl_is_on(void);
extern bool vrdl_should_turn_off(void);
extern bool vrdl_is_key_pressed(vrdl_key key);
extern bool vrdl_is_fullscreen(void);

extern void vrdl_set_title(const char *title);
extern void vrdl_set_display_size(int width, int height);
extern void vrdl_set_display_pos(int x, int y);
extern void vrdl_set_fullscreen(bool fullscreen);

extern const char *vrdl_get_title(void);
extern void vrdl_get_display_size(int *width, int *height);
extern void vrdl_get_display_pos(int *x, int *y);

extern void vrdl_draw_pixel(vrdl_color color);
extern void vrdl_draw_pixels(vrdl_color color, size_t count);
extern void vrdl_draw_pixel_array(vrdl_color *color_array, size_t size);

extern void vrdl_update_display(void);

#endif