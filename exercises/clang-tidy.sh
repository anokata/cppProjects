#!/usr/bin/env bash
 
find . \( -name \*.c -or -name \*.cpp -or -name \*.cc \) |xargs -n1 -P4 clang-tidy
