#!/usr/bin/env bash

clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4, AllowShortFunctionsOnASingleLine: None, KeepEmptyLinesAtTheStartOfBlocks: false}" "$@"

#use:  cleanup-format -i *.{c,h,cc,cpp,hpp,cxx}
#all: find . \( -name \*.c -or -name \*.cpp -or -name \*.cc \) |xargs -n1 -P4 cleanup-tidy
