#include <iostream>
using namespace std;

typedef int ** array2d;

int ** create_array2d(size_t a, size_t b);
void free_array2d(int ** m);

int ** create_array2d(size_t a, size_t b) {
    int ** m = new int * [a];
    m[0] = new int [a * b];
    for (size_t i = 1; i != a; ++i) {
        m[i] = m[i-1] + b;
    }
    return m;
}

void free_array2d(int ** m) {
    delete [] m[0];
    delete [] m;
}

void show_array2d(array2d x, size_t a, size_t b) {
    for (size_t i = 0; i < a; ++i) {
        for (size_t j = 0; j < b; ++j) {
            cout << x[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void init_array2d(array2d x, int val, size_t a, size_t b) {
    for (size_t i = 0; i < a; ++i) {
        for (size_t j = 0; j < b; ++j) {
            x[i][j] = val++;
        }
    }
}

int main() {
    array2d a = create_array2d(2, 3);
    array2d b = create_array2d(2, 3);
    init_array2d(a, 1, 2, 3);
    show_array2d(a, 2, 3);
    show_array2d(b, 2, 3);


    free_array2d(b);
    free_array2d(a);
    return 0;
}
