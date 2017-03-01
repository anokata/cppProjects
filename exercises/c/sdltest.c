#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>

//TODO: basic lines
#define FRAMES_PER_SECOND 20

static uint32_t start = 0;
void start_timer() {
    start = SDL_GetTicks();
}
uint32_t diff_timer() {
    uint32_t old_start = start;
    start = SDL_GetTicks();
    return start - old_start;
}
uint32_t get_timer() {
    uint32_t end = SDL_GetTicks();
    return end - start;
}

int main( int argc, char* args[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Surface* hello = NULL;
    SDL_Surface* screen = NULL;
    SDL_Event event;
    int quit = 0;
    TTF_Font* font = NULL;
    SDL_Color textColor = {255, 0, 255};
    int frame = 0;

    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 20);
    if (!font) {
        perror("openfont");
        exit(1);
    }
    hello = TTF_RenderText_Solid(font, "Hello text", textColor);
    if (hello == NULL) {
        perror("render text");
        return 1;
    }
    SDL_BlitSurface( hello, NULL, screen, NULL );
    SDL_Flip( screen );
    uint32_t* pixels = screen->pixels;
    for (uint32_t x = 0; x < 100; x++) {
        pixels[x*x] = 0xFF0000;
    }
    //lineRGBA(screen, 0, 0, 100, 50, 100, 0, 0, 255);
    aalineRGBA(screen, 0, 0, 100, 50, 100, 0, 0, 200);
    boxColor(screen, 10, 10, 100, 50, 0xFFFF00AA);
    //filledEllipseRGBA(screen, 100, 100, 100, 50, 200, 0, 100, 255);
    aaellipseRGBA(screen, 100, 100, 100, 50, 200, 0, 100, 255);
    while (quit == 0) {
        start_timer();
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
        frame++;
        if (get_timer() < 1000/FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - get_timer() );
            diff_timer();
            //printf("frame delay %d\n", frame);
        }
    }
    SDL_FreeSurface( hello );
    SDL_Quit();
    return 0;
}
