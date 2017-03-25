#include <stdio.h>

#define N 20

void print_arr(int a[N]) {
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void insert_sort(int a[N]) {
    for (int i = 1; i < N; i++) {
        int j = i - 1;
        int t = a[i];
        while (j >= 0 && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

int main() {
    int a[N] = {1,10,15,2,3,12,11,10,9,10,7,3,7};
    print_arr(a);

    insert_sort(a);

    print_arr(a);
    return 0;
}
