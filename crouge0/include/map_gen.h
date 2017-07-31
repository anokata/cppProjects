#pragma once
#ifndef __MAP_GEN__
#define __MAP_GEN__

#define _GNU_SOURCE
#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib/ccurses.h"
#include "util.h"
#include "map.h"


int out_map(char *filename, int width, int heigth);
Map load_map(string filename);
void free_map(Map map);
void print_map(Map map);


char map_char_at(Map map, int x, int y);

int fget_int_line(FILE *file);
Map make_map(int width, int heigth);

Map load_global_map();
void draw_map(Map map);

#endif
