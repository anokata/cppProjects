#include <inttypes.h> // wcstoimax
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
//#define NDEBUG
#include <assert.h>
//#include <ctype.h> // tolower ... // wctype.h
#include <stddef.h>
#include <time.h>

int main() {
    int ab[] = {1, 2, 3};
    const time_t timer = time(NULL);
    printf("%s\n", ctime(&timer));
    struct tm * timeinfo;
    timeinfo = localtime(&timer);
    char * t = asctime(timeinfo);
    printf("%s\n", t);
    char buffer [80];
    strftime (buffer,80,"Now it's %y/%m/%d.",timeinfo);
    puts (buffer);

    void *a;
    printf("pointer size: %lu bytes\n", sizeof(a));
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    printf("_SC_LEVEL1_DCACHE_LINESIZE: %lu bytes\n", l1dcls);
    // dynamic array
    uint32_t n = 0;
    scanf("%" SCNu32, &n);
    assert(n > 2 && "MUST BE > 2");
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
