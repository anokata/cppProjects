P=rouge0
MAPGEN=mapgen
CFLAGS=-Wall -std=gnu11 -g 
OBJECTS=app.c main.c
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

MAP_OBJECTS=map_gen.c

map:
	$(CC) $(CFLAGS) $(MAP_OBJECTS) -L../ccurses -lccurses -I./include -I../ccurses -lncurses -o /tmp/$(MAPGEN) && valgrind /tmp/$(MAPGEN) && ls -l /tmp/*.map

