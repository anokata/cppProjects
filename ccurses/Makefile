LIB=libfurses.a
CC=gcc

main:
	#$CC -Wall -std=c11 *.c furses/*.c -lncurses -o /tmp/a.out && /tmp/a.out
	$(CC) -Wall -std=c11 *.c -lncurses -o /tmp/a.out && /tmp/a.out

makelib:
	$(CC) -std=c11 furses/*.c -c
	ar rvs libfurses.a *.o
	rm *.o
	# make to temp

make_with_lib:
	$(CC) -Wall -std=c11 *.c -L../curses_framework -lfurses -I../curses_framework -lncurses -o /tmp/a.out && /tmp/a.out
