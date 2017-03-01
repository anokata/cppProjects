#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_framerate.h>
#include <glib.h>

//TODO: 

#define FRAMES_PER_SECOND 60

static FPSmanager frames;
static SDL_Surface* screen = NULL;
static TTF_Font* font = NULL;
static SDL_Surface* hello = NULL;

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
    SDL_Color textColor = {255, 0, 255};
    SDL_Color bgColor = {0, 0, 0};
    hello = TTF_RenderText_Shaded(font, "Hello text", textColor, bgColor);
    if (hello == NULL) {
        perror("render text");
        return -1;
    }
    SDL_Rect r = {10, 200};
    SDL_BlitSurface( hello, NULL, screen, &r );
    SDL_Flip( screen );
    boxColor(screen, 10, 10, 100, 50, 0xFFFF00AA);
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
        SDL_Flip( screen );
        SDL_framerateDelay(&frames);
    }
    return 0;
}

void 
sdl_free() {
    SDL_FreeSurface( hello );
    SDL_Quit();
}

void glibtest() {
    GList *l = NULL;
    int z = 0x00414200;
    l = g_list_append(l, "first");
    l = g_list_append(l, &z);
    l = g_list_append(l, "t");
    GList *p = l;
    while (p != NULL) {
        char* str = p->data;
        printf("%s\n", str);
        p = p->next;
    }
    g_list_free(l);
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
