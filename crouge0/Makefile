P=rouge0
MAPGEN=mapgen_main
CFLAGS=-Wall -std=gnu11 -g 
OBJECTS=app.c main.c map_gen.c world_map.c g.c tile_map.c util.c
MAP_OBJECTS=mapgen_main.c map_gen.c
TMAP_OBJECTS=tile_map.c test_tile_map.c util.c
LDLIBS=
LIB=libfurses.a
CC=gcc

main:
	$(CC) $(CFLAGS) $(OBJECTS) -L../ccurses -lccurses -I./include -I../ccurses -lncurses -o /tmp/$(P) && /tmp/$(P)

compile:
	$(CC) $(CFLAGS) *.c -L../ccurses -lccurses -I../ccurses -lncurses -o /tmp/$(P)

makelib:
	$(CC) -std=c11 lib/*.c -c
	ar rvs libccurses.a *.o
	rm *.o
	# make to temp

make_with_lib:
	$(CC) -Wall -std=c11 *.c -L../ccurses -lccurses -I../ccurses -lncurses -o /tmp/a.out && /tmp/a.out


map:
	$(CC) $(CFLAGS) $(MAP_OBJECTS) -L../ccurses -lccurses -I./include -I../ccurses -lncurses -o /tmp/$(MAPGEN) && valgrind /tmp/$(MAPGEN) && ls -l /tmp/*.map

tmap:
	$(CC) $(CFLAGS) $(TMAP_OBJECTS) -L../ccurses -lccurses -I./include -I../ccurses -lncurses -o /tmp/out && valgrind /tmp/out

