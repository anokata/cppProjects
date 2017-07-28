#pragma once
#ifndef __MAP_GEN__
#define __MAP_GEN__

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib/ccurses.h"
#include "util.h"
#include "map.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

int out_map(char *filename, int width, int heigth);
Map load_map(string filename);
void free_map(Map map);
void print_map(Map map);


char map_char_at(Map map, int x, int y);


string load_global_map();

#endif
