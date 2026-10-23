#include <vrdl.h>
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

static vrdl_state vrdl = (vrdl_state){0};

static void vrdl_resize(void) {
    dword width, height;
    SDL_GetWindowSize(vrdl.display, &width, &height);
    
    if (height * vrdl.aspect_ratio > width) {
        vrdl.display_rect.x = 0;
        vrdl.display_rect.w = width;
        vrdl.display_rect.h = width / vrdl.aspect_ratio;
        vrdl.display_rect.y = (height >> 1) - vrdl.display_rect.h / 2;
    } else {
        vrdl.display_rect.y = 0;
        vrdl.display_rect.h = height;
        vrdl.display_rect.w = height * vrdl.aspect_ratio;
        vrdl.display_rect.x = (width >> 1) - vrdl.display_rect.w / 2;
    }
}

static bool vrdl_update_image(void) {
    uint32_t image_height;

    if (vrdl.display_type) {
        vrdl.image_rect.x = 0;
        vrdl.image_rect.y = 0;
        vrdl.line_width   = vrdl.image_rect.w;
        image_height      = vrdl.image_rect.h;
    } else {
        vrdl.image_rect.x = vrdl.blank.h >> 1;
        vrdl.image_rect.y = vrdl.blank.v >> 1;
        vrdl.line_width   = vrdl.image_rect.w + vrdl.blank.h;
        image_height      = vrdl.image_rect.h + vrdl.blank.v;
    }
    
    SDL_Texture *new_image = SDL_CreateTexture(
        vrdl.render,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        vrdl.line_width, image_height
    );
    if (!new_image) return false;

    SDL_SetTextureScaleMode(new_image, SDL_SCALEMODE_NEAREST);

    vrdl.image_area = vrdl.line_width * image_height;
    vrdl_color *new_pixels = (vrdl_color*)malloc(vrdl.image_area * sizeof(vrdl_color));
    if (!new_pixels) {
        SDL_DestroyTexture(new_image);
        return false;
    }

    if (vrdl.image) SDL_DestroyTexture(vrdl.image);
    if (vrdl.pixels) free(vrdl.pixels);

    vrdl.image = new_image;
    vrdl.pixels = new_pixels;
    vrdl.beam = 0;

    return true;
}

bool vrdl_turn_on(int width, int height, vrdl_display_type display_type) {
    if (vrdl_is_on() ||
        display_type > VRDL_DISPLAY_TYPE_LCD
    ) return false;

    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    if (!(vrdl.display = SDL_CreateWindow("VRDL Window", width, height, 0))) {
        vrdl_turn_off();
        return false;
    }

    if (!(vrdl.render = SDL_CreateRenderer(vrdl.display, NULL))) {
        vrdl_turn_off();
        return false;
    }
    SDL_SetRenderVSync(vrdl.render, 1);

    if (display_type)
        vrdl_set_resolution(VRDL_DEFAULT_RESOLUTION_WIDTH, VRDL_DEFAULT_RESOLUTION_HEIGHT);
    else
        vrdl_set_resolution_and_blanking(
            VRDL_DEFAULT_RESOLUTION_WIDTH,
            VRDL_DEFAULT_RESOLUTION_HEIGHT,
            VRDL_DEFAULT_HBLANK,
            VRDL_DEFAULT_VBLANK
        );

    vrdl.display_type = display_type;
    vrdl.should_turn_off = false;
    vrdl.aspect_ratio = (double)width / height;
    vrdl.frame_rate = VRDL_DEFAULT_FRAME_RATE;
    vrdl.time_step = 1.0 / vrdl.frame_rate;
    vrdl.frequency = SDL_GetPerformanceFrequency();
    vrdl.frame_end = SDL_GetPerformanceCounter();
    vrdl.accumulator = 0.0;

    vrdl_resize();

    return true;
}
void vrdl_turn_off(void) {
    if (vrdl.pixels) free(vrdl.pixels);
    if (vrdl.image) SDL_DestroyTexture(vrdl.image);
    if (vrdl.render) SDL_DestroyRenderer(vrdl.render);
    if (vrdl.display) SDL_DestroyWindow(vrdl.display);
    if (vrdl_is_on()) SDL_Quit();
    memset(&vrdl, 0, sizeof(vrdl));
}

void vrdl_request_turn_off(void) {
    vrdl.should_turn_off = true;
}
bool vrdl_should_turn_off(void) {
    return vrdl.should_turn_off;
}

bool vrdl_set_resolution(uint32_t width, uint32_t height) {
    if (!vrdl_is_on() ||
        !(width && height)
    ) return false;

    vrdl.image_rect.w = width;
    vrdl.image_rect.h = height;
    return vrdl_update_image();
}
bool vrdl_set_blanking(uint32_t hblank, uint32_t vblank) {
    if (!vrdl_is_on() ||
        vrdl.display_type ||
        !(hblank && vblank) ||
        ((hblank & 1) || (vblank & 1))
    ) return false;

    vrdl.blank.h = hblank;
    vrdl.blank.v = vblank;
    return vrdl_update_image();
}
bool vrdl_set_resolution_and_blanking(uint32_t width, uint32_t height, uint32_t hblank, uint32_t vblank) {
    if (!vrdl_is_on() ||
        !(width && height)
    ) return false;

    if (vrdl.display_type) {
        vrdl.image_rect.w = width;
        vrdl.image_rect.h = height;

        return vrdl_update_image();
    } else if (
        !(hblank && vblank) ||
        ((hblank & 1) || (vblank & 1))
    ) {
        vrdl.image_rect.w = width;
        vrdl.image_rect.h = height;
        vrdl.blank.h = hblank;
        vrdl.blank.v = vblank;

        return vrdl_update_image();
    } else return false;
}

bool vrdl_is_on(void) {
    return SDL_WasInit(0) != 0;
}
bool vrdl_is_frame_active(void) {
    return vrdl.accumulator >= vrdl.time_step;
}
bool vrdl_is_key_pressed(vrdl_key key) {
    return (vrdl.keyboard && key < SDL_SCANCODE_COUNT) ? vrdl.keyboard[key] : false;
}
bool vrdl_is_fullscreen(void) {
    return vrdl_is_on() ? SDL_GetWindowFlags(vrdl.display) & SDL_WINDOW_FULLSCREEN : false;
}
bool vrdl_is_resizable(void) {
    return vrdl_is_on() ? SDL_GetWindowFlags(vrdl.display) & SDL_WINDOW_RESIZABLE : false;
}

void vrdl_set_title(const char *title) {
    if (vrdl_is_on()) SDL_SetWindowTitle(vrdl.display, title);
}
void vrdl_set_display_size(int width, int height) {
    if (vrdl_is_on()) SDL_SetWindowSize(vrdl.display, width, height);
}
void vrdl_set_display_pos(int x, int y) {
    if (vrdl_is_on()) SDL_SetWindowPosition(vrdl.display, x, y);
}
void vrdl_set_fullscreen(bool fullscreen) {
    if (vrdl_is_on()) SDL_SetWindowFullscreen(vrdl.display, fullscreen);
}
void vrdl_set_aspect_ratio(double aspect_ratio) {
    if (aspect_ratio) vrdl.aspect_ratio = aspect_ratio;
    else {
        int width, height;
        SDL_GetWindowSize(vrdl.display, &width, &height);
        vrdl.aspect_ratio = (double)width / height;
    }
    vrdl_resize();
}
void vrdl_set_resizable(bool resizable) {
    if (vrdl_is_on()) SDL_SetWindowResizable(vrdl.display, resizable);
}
void vrdl_set_frame_rate(double frame_rate) {
    vrdl.frame_rate = frame_rate;
    vrdl.time_step = 1.0 / frame_rate;
}

const char *vrdl_get_title(void) {
    return vrdl_is_on() ? SDL_GetWindowTitle(vrdl.display) : NULL;
}
void vrdl_get_display_size(int *width, int *height) {
    if (vrdl_is_on()) SDL_GetWindowSize(vrdl.display, width, height);
}
void vrdl_get_display_pos(int *x, int *y) {
    if (vrdl_is_on()) SDL_GetWindowPosition(vrdl.display, x, y);
}
double vrdl_get_aspect_ratio(void) { return vrdl.aspect_ratio; }
double vrdl_get_frame_rate(void) { return vrdl.frame_rate; }

#define _draw_pixel(color) \
    vrdl.pixels[vrdl.beam++] = color; \
    if (vrdl.beam >= vrdl.image_area) { \
        vrdl.beam -= vrdl.image_area; \
        if (vrdl.accumulator >= vrdl.time_step) \
            vrdl.accumulator -= vrdl.time_step; \
    }

void vrdl_draw_pixel(vrdl_color color) {
    if (vrdl.image) _draw_pixel(color)
}
void vrdl_draw_pixels(vrdl_color color, size_t count) {
    if (vrdl.image) for (size_t i = 0; i < count; ++i) _draw_pixel(color)
}
void vrdl_draw_pixel_array(vrdl_color *color_array, size_t size) {
    if (vrdl.image && color_array) for (size_t i = 0; i < size;) _draw_pixel(color_array[i++])
}

void vrdl_update_display(void) {
    if (!vrdl_is_on()) return;

    uint64_t frame_start = SDL_GetPerformanceCounter();
    
    double frame_time = (double)(frame_start - vrdl.frame_end) / vrdl.frequency;
    if (frame_time > 0.25) frame_time = 0.25;

    vrdl.accumulator += frame_time;
    vrdl.frame_end = frame_start;

    SDL_RenderClear(vrdl.render);
    if (vrdl.image) {
        SDL_UpdateTexture(vrdl.image, NULL, vrdl.pixels, vrdl.line_width * sizeof(vrdl_color));
        SDL_RenderTexture(vrdl.render, vrdl.image, &vrdl.image_rect, &vrdl.display_rect);
    }
    SDL_RenderPresent(vrdl.render);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT: vrdl.should_turn_off = true; break;
            case SDL_EVENT_WINDOW_RESIZED: vrdl_resize();
        }
    }

    if (!vrdl.keyboard) vrdl.keyboard = SDL_GetKeyboardState(NULL);
}