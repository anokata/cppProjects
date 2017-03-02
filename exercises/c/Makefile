build: 
	gcc solution.c -o solution
sdl: 
	gcc sdltest.c -lSDL -lSDL_ttf -lSDL_gfx `pkg-config --cflags --libs glib-2.0` -o sdltest && ./sdltest
one: 
	gcc sdltest.c -lSDL -lSDL_ttf -lSDL_gfx `pkg-config --cflags --libs glib-2.0` -o sdltest && ./sdltest
debug: 
	gcc sdltest.c -g -lSDL -lSDL_ttf -lSDL_gfx `pkg-config --cflags --libs glib-2.0` -o sdltest && ./sdltest
