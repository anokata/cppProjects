#include <stdio.h>
#include <string.h>

int main () {
    int size = 8;
    int arr[size];
    arr[size-1] = size;
    arr[1] = size;
    arr[0] = size;
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    // alloca
    return 0;
}

