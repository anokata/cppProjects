LIB = libfurses.a
CC = g++

main:
	g++ -Wall -std=c++11 *.cpp furses/*.cpp -lncurses -o /tmp/a.out && /tmp/a.out

makelib:
	g++ -std=c++11 furses/*.cpp -c
	ar rvs libfurses.a *.o
	rm *.o
	# make to temp

make_with_lib:
	g++ -Wall -std=c++11 *.cpp -L../curses_framework -lfurses -I../curses_framework -lncurses -o /tmp/a.out && /tmp/a.out
