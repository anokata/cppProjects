#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    void *a;
    printf("pointer size: %lu bytes\n", sizeof(a));
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    printf("_SC_LEVEL1_DCACHE_LINESIZE: %lu bytes\n", l1dcls);
    // dynamic array
    uint32_t n = 0;
    scanf("%" SCNu32, &n);
    uint32_t array[n];
    for (uint32_t i = 0; i < n; i++) {
        array[i] = i * i * 3;
    }
    for (uint32_t i = 0; i < n; i++) {
        printf("%" PRIu32 ", ", array[i] / 2);
    }
    printf("\n%" PRIu32, n);
    return 0;
}
