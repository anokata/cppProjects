#include <stdio.h>

#define N 20
#define T 5

void print_arr(int a[N]) 
{
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int insert_sort(int a[N]) 
{
    int count = 0;
    for (int i = 1; i < N; i++) {
        int j = i - 1;
        int t = a[i];
        while (j >= 0 && a[j] > t) {
            a[j + 1] = a[j];
            j--;
            count++;
        }
        a[j + 1] = t;
    }
    return count;
}

int shell_sort(int a[N]) 
{
    int d = N/2;
    int t;
    int count = 0;
    while (d) {
        for (int i = 0; i < N - d; i++) {
            if (a[i] > a[i+d]) {
                t = a[i];
                a[i] = a[i+d];
                a[i+d] = t;
            }
            count++;
        }
        d /= 2;
    }
    count += insert_sort(a);
    return count;
}

int main() 
{
    int a[N] = {1,10,15,2,3,12,11,10,9,10,7,3,7};
    int b[N] = {1,10,15,2,3,12,11,10,9,10,7,3,7};

    print_arr(a);
    /*int c[T] = {0};
    for (int i = 0; i < T; i++) {
        c[i] = insert_sort(a);
    }
    */
    //insert_sort(a); //check ok sort TODO

    int c = shell_sort(b);
    printf("shell sort count: %d\n", c);
    c = insert_sort(a);
    printf("insert sort count: %d\n", c);

    print_arr(a);
    return 0;
}
