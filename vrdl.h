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

#define VRDL_DEFAULT_FRAME_RATE 60.0

typedef uint32_t vrdl_color;

#define vrdl_color_rgb(r, g, b) (vrdl_color)((byte)(r) + ((byte)(g) << 8) + ((byte)(b) << 16) + 0xff000000)
#define vrdl_color_rgba(r, g, b, a) (vrdl_color)((byte)(r) + ((byte)(g) << 8) + ((byte)(b) << 16) + ((byte)(a) << 24))

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

#ifdef __cplusplus
extern "C" {
#endif

extern bool vrdl_turn_on(int width, int height, vrdl_display_type display_type);
extern void vrdl_turn_off(void);

extern void vrdl_request_turn_off(void);
extern bool vrdl_should_turn_off(void);

extern bool vrdl_set_resolution(uint32_t width, uint32_t height);
extern bool vrdl_set_blanking(uint32_t hblank, uint32_t vblank);
extern bool vrdl_set_resolution_and_blanking(uint32_t width, uint32_t height, uint32_t hblank, uint32_t vblank);

extern bool vrdl_is_on(void);
extern bool vrdl_is_frame_active(void);
extern bool vrdl_is_key_pressed(vrdl_key key);
extern bool vrdl_is_fullscreen(void);
extern bool vrdl_is_resizable(void);

extern void vrdl_set_title(const char *title);
extern void vrdl_set_display_size(int width, int height);
extern void vrdl_set_display_pos(int x, int y);
extern void vrdl_set_fullscreen(bool fullscreen);
extern void vrdl_set_aspect_ratio(double aspect_ratio);
extern void vrdl_set_resizable(bool resizable);
extern void vrdl_set_frame_rate(double frame_rate);

extern const char *vrdl_get_title(void);
extern void vrdl_get_display_size(int *width, int *height);
extern void vrdl_get_display_pos(int *x, int *y);
extern double vrdl_get_aspect_ratio(void);
extern double vrdl_get_frame_rate(void);

extern void vrdl_draw_pixel(vrdl_color color);
extern void vrdl_draw_pixels(vrdl_color color, size_t count);
extern void vrdl_draw_pixel_array(vrdl_color *color_array, size_t size);

extern void vrdl_update_display(void);

#ifdef __cplusplus
}
#endif

#if defined(VRDL_IMPLEMENTATION) || defined(VGLIN_IMPLEMENTATION)
#define VRDL_IMPLEMENTATION_INCLUDED (1)

#include <SDL3/SDL.h>

typedef struct {
    vrdl_display_type display_type;
    SDL_Window *display;
    SDL_Renderer *render;

    SDL_Texture *image;
    vrdl_color *pixels;
    size_t image_area;
    size_t line_width;
    size_t beam;

    SDL_FRect image_rect;
    SDL_FRect display_rect;
    double aspect_ratio;

    struct {
        uint32_t h;
        uint32_t v;
    } blank;

    double frame_rate;
    double time_step;
    Uint64 frequency;
    Uint64 frame_end;
    double accumulator;

    bool should_turn_off;
    const bool *keyboard;
} vrdl_state;

static vrdl_state _vrdl = {0};

static void _vrdl_resize(void) {
    dword width, height;
    SDL_GetWindowSize(_vrdl.display, &width, &height);
    
    if (height * _vrdl.aspect_ratio > width) {
        _vrdl.display_rect.x = 0;
        _vrdl.display_rect.w = width;
        _vrdl.display_rect.h = width / _vrdl.aspect_ratio;
        _vrdl.display_rect.y = (height >> 1) - _vrdl.display_rect.h / 2;
    } else {
        _vrdl.display_rect.y = 0;
        _vrdl.display_rect.h = height;
        _vrdl.display_rect.w = height * _vrdl.aspect_ratio;
        _vrdl.display_rect.x = (width >> 1) - _vrdl.display_rect.w / 2;
    }
}

static bool _vrdl_update_image(void) {
    uint32_t image_height;

    if (_vrdl.display_type) {
        _vrdl.image_rect.x = 0;
        _vrdl.image_rect.y = 0;
        _vrdl.line_width   = _vrdl.image_rect.w;
        image_height       = _vrdl.image_rect.h;
    } else {
        _vrdl.image_rect.x = _vrdl.blank.h >> 1;
        _vrdl.image_rect.y = _vrdl.blank.v >> 1;
        _vrdl.line_width   = _vrdl.image_rect.w + _vrdl.blank.h;
        image_height       = _vrdl.image_rect.h + _vrdl.blank.v;
    }
    
    SDL_Texture *new_image = SDL_CreateTexture(
        _vrdl.render,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        _vrdl.line_width, image_height
    );
    if (!new_image) return false;

    SDL_SetTextureScaleMode(new_image, SDL_SCALEMODE_NEAREST);

    _vrdl.image_area = _vrdl.line_width * image_height;
    vrdl_color *new_pixels = (vrdl_color*)malloc(_vrdl.image_area * sizeof(vrdl_color));
    if (!new_pixels) {
        SDL_DestroyTexture(new_image);
        return false;
    }

    if (_vrdl.image) SDL_DestroyTexture(_vrdl.image);
    if (_vrdl.pixels) free(_vrdl.pixels);

    _vrdl.image = new_image;
    _vrdl.pixels = new_pixels;
    _vrdl.beam = 0;

    return true;
}

bool vrdl_turn_on(int width, int height, vrdl_display_type display_type) {
    if (vrdl_is_on() ||
        display_type > VRDL_DISPLAY_TYPE_LCD
    ) return false;

    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    if (!(_vrdl.display = SDL_CreateWindow("VRDL Window", width, height, 0))) {
        vrdl_turn_off();
        return false;
    }

    if (!(_vrdl.render = SDL_CreateRenderer(_vrdl.display, NULL))) {
        vrdl_turn_off();
        return false;
    }
    SDL_SetRenderVSync(_vrdl.render, 1);

    if (display_type)
        vrdl_set_resolution(VRDL_DEFAULT_RESOLUTION_WIDTH, VRDL_DEFAULT_RESOLUTION_HEIGHT);
    else
        vrdl_set_resolution_and_blanking(
            VRDL_DEFAULT_RESOLUTION_WIDTH,
            VRDL_DEFAULT_RESOLUTION_HEIGHT,
            VRDL_DEFAULT_HBLANK,
            VRDL_DEFAULT_VBLANK
        );

    _vrdl.display_type = display_type;
    _vrdl.should_turn_off = false;
    _vrdl.aspect_ratio = (double)width / height;
    _vrdl.frame_rate = VRDL_DEFAULT_FRAME_RATE;
    _vrdl.time_step = 1.0 / _vrdl.frame_rate;
    _vrdl.frequency = SDL_GetPerformanceFrequency();
    _vrdl.frame_end = SDL_GetPerformanceCounter();
    _vrdl.accumulator = 0.0;

    _vrdl_resize();

    return true;
}
void vrdl_turn_off(void) {
    if (_vrdl.pixels) free(_vrdl.pixels);
    if (_vrdl.image) SDL_DestroyTexture(_vrdl.image);
    if (_vrdl.render) SDL_DestroyRenderer(_vrdl.render);
    if (_vrdl.display) SDL_DestroyWindow(_vrdl.display);
    if (vrdl_is_on()) SDL_Quit();
    memset(&_vrdl, 0, sizeof(_vrdl));
}

void vrdl_request_turn_off(void) {
    _vrdl.should_turn_off = true;
}
bool vrdl_should_turn_off(void) {
    return _vrdl.should_turn_off;
}

bool vrdl_set_resolution(uint32_t width, uint32_t height) {
    if (!vrdl_is_on() ||
        !(width && height)
    ) return false;

    _vrdl.image_rect.w = width;
    _vrdl.image_rect.h = height;
    return _vrdl_update_image();
}
bool vrdl_set_blanking(uint32_t hblank, uint32_t vblank) {
    if (!vrdl_is_on() ||
        _vrdl.display_type ||
        !(hblank && vblank) ||
        ((hblank & 1) || (vblank & 1))
    ) return false;

    _vrdl.blank.h = hblank;
    _vrdl.blank.v = vblank;
    return _vrdl_update_image();
}
bool vrdl_set_resolution_and_blanking(uint32_t width, uint32_t height, uint32_t hblank, uint32_t vblank) {
    if (!vrdl_is_on() ||
        !(width && height)
    ) return false;

    if (_vrdl.display_type) {
        _vrdl.image_rect.w = width;
        _vrdl.image_rect.h = height;

        return _vrdl_update_image();
    } else if (
        (hblank && vblank) ||
        !((hblank & 1) || (vblank & 1))
    ) {
        _vrdl.image_rect.w = width;
        _vrdl.image_rect.h = height;
        _vrdl.blank.h = hblank;
        _vrdl.blank.v = vblank;

        return _vrdl_update_image();
    } else return false;
}

bool vrdl_is_on(void) {
    return SDL_WasInit(0) != 0;
}
bool vrdl_is_frame_active(void) {
    return _vrdl.accumulator >= _vrdl.time_step;
}
bool vrdl_is_key_pressed(vrdl_key key) {
    return (_vrdl.keyboard && key < SDL_SCANCODE_COUNT) ? _vrdl.keyboard[key] : false;
}
bool vrdl_is_fullscreen(void) {
    return vrdl_is_on() ? SDL_GetWindowFlags(_vrdl.display) & SDL_WINDOW_FULLSCREEN : false;
}
bool vrdl_is_resizable(void) {
    return vrdl_is_on() ? SDL_GetWindowFlags(_vrdl.display) & SDL_WINDOW_RESIZABLE : false;
}

void vrdl_set_title(const char *title) {
    if (vrdl_is_on())
        SDL_SetWindowTitle(_vrdl.display, title);
}
void vrdl_set_display_size(int width, int height) {
    if (vrdl_is_on())
        SDL_SetWindowSize(_vrdl.display, width, height);
}
void vrdl_set_display_pos(int x, int y) {
    if (vrdl_is_on())
        SDL_SetWindowPosition(_vrdl.display, x, y);
}
void vrdl_set_fullscreen(bool fullscreen) {
    if (vrdl_is_on())
        SDL_SetWindowFullscreen(_vrdl.display, fullscreen);
}
void vrdl_set_aspect_ratio(double aspect_ratio) {
    if (aspect_ratio) _vrdl.aspect_ratio = aspect_ratio;
    else {
        int width, height;
        SDL_GetWindowSize(_vrdl.display, &width, &height);
        _vrdl.aspect_ratio = (double)width / height;
    }
    _vrdl_resize();
}
void vrdl_set_resizable(bool resizable) {
    if (vrdl_is_on()) SDL_SetWindowResizable(_vrdl.display, resizable);
}
void vrdl_set_frame_rate(double frame_rate) {
    _vrdl.frame_rate = frame_rate;
    _vrdl.time_step = 1.0 / frame_rate;
}

const char *vrdl_get_title(void) {
    return vrdl_is_on() ? SDL_GetWindowTitle(_vrdl.display) : NULL;
}
void vrdl_get_display_size(int *width, int *height) {
    if (vrdl_is_on())
        SDL_GetWindowSize(_vrdl.display, width, height);
}
void vrdl_get_display_pos(int *x, int *y) {
    if (vrdl_is_on())
        SDL_GetWindowPosition(_vrdl.display, x, y);
}
double vrdl_get_aspect_ratio(void) { return _vrdl.aspect_ratio; }
double vrdl_get_frame_rate(void) { return _vrdl.frame_rate; }

#define _draw_pixel(color) \
    _vrdl.pixels[_vrdl.beam++] = color; \
    if (_vrdl.beam >= _vrdl.image_area) { \
        _vrdl.beam -= _vrdl.image_area; \
        if (_vrdl.accumulator >= _vrdl.time_step) \
            _vrdl.accumulator -= _vrdl.time_step; \
    }

void vrdl_draw_pixel(vrdl_color color) {
    if (_vrdl.image) {_draw_pixel(color)}
}
void vrdl_draw_pixels(vrdl_color color, size_t count) {
    if (_vrdl.image) for (size_t i = 0; i < count; ++i) {_draw_pixel(color)}
}
void vrdl_draw_pixel_array(vrdl_color *color_array, size_t size) {
    if (_vrdl.image && color_array) for (size_t i = 0; i < size;) {_draw_pixel(color_array[i++])}
}

void vrdl_update_display(void) {
    if (!vrdl_is_on()) return;

    uint64_t frame_start = SDL_GetPerformanceCounter();
    
    double frame_time = (double)(frame_start - _vrdl.frame_end) / _vrdl.frequency;
    if (frame_time > 0.25) frame_time = 0.25;

    _vrdl.accumulator += frame_time;
    _vrdl.frame_end = frame_start;

    SDL_RenderClear(_vrdl.render);
    if (_vrdl.image) {
        SDL_UpdateTexture(_vrdl.image, NULL, _vrdl.pixels, _vrdl.line_width * sizeof(vrdl_color));
        SDL_RenderTexture(_vrdl.render, _vrdl.image, &_vrdl.image_rect, &_vrdl.display_rect);
    }
    SDL_RenderPresent(_vrdl.render);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT: _vrdl.should_turn_off = true; break;
            case SDL_EVENT_WINDOW_RESIZED: _vrdl_resize();
        }
    }

    if (!_vrdl.keyboard) _vrdl.keyboard = SDL_GetKeyboardState(NULL);
}
#endif

#endif