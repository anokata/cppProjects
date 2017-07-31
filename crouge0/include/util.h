#pragma once
#ifndef __UTIL__
#define __UTIL__
typedef char* string;

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

#endif
