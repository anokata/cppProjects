#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_framerate.h>
#include <glib.h>
#include <string.h>

//TODO: 

#define FRAMES_PER_SECOND 60

typedef struct {
    SDL_Color text_color;
    SDL_Color rect_color;
	uint32_t padx;
	uint32_t pady;
} node_options;

typedef struct {
    char* text;
    char texts[32];
	char selected;
	node_options* options;
	// pointer to option struct
} list_node;
// struct for common node options like padding, colors
// constructor for default

void render_list(SDL_Surface* surface, GList* list, uint32_t x, uint32_t y);

static FPSmanager frames;
static SDL_Surface* screen = NULL;
static TTF_Font* font = NULL;

static GList* test_list = NULL;

int 
sdl_init() {
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_initFramerate(&frames);
    SDL_setFramerate(&frames, FRAMES_PER_SECOND);
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 20);
    if (!font) {
        perror("openfont");
        return -1;
    }
    return 0;
}

int 
init_render() {
    SDL_Rect r = {200, 200};
    SDL_Flip( screen );
    return 0;
}

int 
main_loop() {
    SDL_Event event;
    int quit = 0;
    while (quit == 0) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = 1;
            if (event.type == SDL_KEYDOWN) {
                uint8_t *keystates = SDL_GetKeyState( NULL );
                //if (keystates[SDLK_C 
                //GetModState
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = 1; break;
                    default: printf("key%d\n", event.key.keysym.sym); 
                }
            }
        }
        render_list(screen, test_list, 100, 50);
        SDL_Flip(screen);
        SDL_framerateDelay(&frames);
    }
    return 0;
}

void 
sdl_free() {
    SDL_Quit();
}



void render_list(SDL_Surface* surface, GList* list, uint32_t x, uint32_t y) {
    uint32_t height = 30;
    uint32_t width = 20;
    list_node* p = NULL;
    GList* cur = list;
	node_options* options = NULL;
    SDL_Surface* img = NULL;
    SDL_Rect r;
	r.y = y;
    while (cur != NULL) {
        // void render_boxnode(list_node* p)
		r.x = x;
        p = cur->data;
		options = p->options;
        img = TTF_RenderText_Shaded(font, p->texts, options->text_color, options->rect_color);
		width = img->w + options->padx; 
		height = img->h + options->pady;
        Uint32 rgbColor = SDL_MapRGB(screen->format, 
				options->rect_color.r, 
				options->rect_color.g, 
				options->rect_color.b);
        boxRGBA(screen, r.x, r.y, r.x + width, r.y+height, 
                options->rect_color.r,
                options->rect_color.g,
                options->rect_color.b,
                255
                );
		r.x += (width - img->w) / 2;
		r.y += (height - img->h) / 2;
        SDL_BlitSurface(img, NULL, screen, &r);
        cur = cur->next;
        r.y += height;
    }
}

void glibtest() {
	static node_options opts = {{0x60, 0x80, 0xC0}, {0x30, 0, 0x40}, 30, 10};
    static list_node node1 = {NULL, "AbcD", 0, &opts};
    test_list = g_list_append(test_list, &node1);
    static list_node node2 = {NULL, "[text node.]", 0, &opts};
    test_list = g_list_append(test_list, &node2);
    //g_list_free(l);
}

int 
main( int argc, char* args[] )
{
    glibtest();
    sdl_init();
    init_render();
    main_loop();
    sdl_free();
    return 0;
}
