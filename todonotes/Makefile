# vim: filetype=make
P=todonotes
CFLAGS=-Wall -Wextra -std=gnu11 -g -D_GNU_SOURCE=1
OBJECTS=main.c
CC=gcc
TARGET=/tmp/$(P)
TEMPOUT=-o $(TARGET)
RUN=$(TARGET)

main: 
	$(CC) $(CFLAGS) $(OBJECTS) $(TEMPOUT) && $(RUN)

run:
	$(RUN)

compile:
	$(CC) $(CFLAGS) $(OBJECTS) $(TEMPOUT)

test:
	valgrind $(RUN)

.PHONY=main run compile test
