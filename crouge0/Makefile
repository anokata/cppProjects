LIB=libfurses.a
CC=gcc

main:
	$(CC) -Wall -std=c11 *.c lib/*.c -lncurses -o /tmp/a.out && /tmp/a.out

makelib:
	$(CC) -std=c11 lib/*.c -c
	ar rvs libccurses.a *.o
	rm *.o
	# make to temp

make_with_lib:
	$(CC) -Wall -std=c11 *.c -L../ccurses -lccurses -I../ccurses -lncurses -o /tmp/a.out && /tmp/a.out
