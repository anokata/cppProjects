#include <iostream>
#include <cstddef>
using namespace std;


int ** create_array2d(size_t a, size_t b);
void free_array2d(int ** m);

typedef int ** array2d;

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

int ** transpose(const int * const * m, unsigned rows, unsigned cols) {
    int ** transposed = create_array2d(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = m[i][j];
        }
    }
    return transposed;
}

int find_min_row(int ** x, size_t rows, size_t cols) {
    int min = x[0][0];
    int min_row = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (x[i][j] < min) {
                min = x[i][j];
                min_row = i;
            }
        }
    }
    return min_row;
}

void swap_min(int *m[], unsigned rows, unsigned cols) {
    int min = find_min_row(m, rows, cols);
    if (min == 0) return;
    int t;
    for (size_t j = 0; j < cols; ++j) {
        t = m[0][j];
        m[0][j] = m[min][j];
        m[min][j] = t;
    }
}

int main() {
    array2d a = create_array2d(2, 3);
    array2d b = create_array2d(2, 3);
    init_array2d(a, 1, 2, 3);
    show_array2d(a, 2, 3);
    //show_array2d(b, 2, 3);

    array2d c = transpose(a, 2, 3);
    c[1][0] = 0;
    show_array2d(c, 3, 2);

    //cout << find_min_row(c, 3, 2);
    swap_min(c, 3, 2);
    show_array2d(c, 3, 2);

    free_array2d(b);
    free_array2d(a);
    free_array2d(c);
    return 0;
}
