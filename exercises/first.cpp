#include <iostream>
#include <cmath>
using namespace std;


#define MAX(x, y, r) {int _a = x; int _b=y; r=_a>_b?_a:_b;}
void show_array(int array[], unsigned length) {
    cout << '[';
    for (int i = 0; i < length - 1; ++i) {
        cout << array[i] << ", ";
    }
    cout << array[length - 1];
    cout << ']'<< endl;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void rotate_one(int a[], unsigned size) {
    for (int i = 0; i < size - 1; ++i) {
        swap(a + i, a + i + 1);
    }
    return;
}

void rotate(int a[], unsigned size, int shift) {
    if (shift == 0 || shift == size) return;
    if (shift > size) {
        shift = shift % size;
    }
    for (int i = 0; i < shift; ++i) {
        rotate_one(a, size);
    }
}

void rotate_(int a[], unsigned size, int shift) {
    if (shift == 0 || shift == size) return;
    if (shift > size) {
        shift = shift % size;
    }
    for (int i = 0; i < size - shift; ++i) {
        cout << i << ' ' << i + shift << endl;
        swap(a + i, a + i + shift);
    }
    

    return;
}

void sq_root_equasion(int a, int b, int c) {
    int d = b * b - 4 * a * c;
    cout << d;
    if (d < 0) {
        cout << "No real roots" << endl;
    } else {
        long x1 = (-b + sqrt(d)) / (2 * a);
        long x2 = (-b - sqrt(d)) / (2 * a);
        cout << x1 << ' ' << x2 << endl;
    }
}

int log_int(int x) {
    if (x < 2) return 0;
    int log = 0;
    long value = 2;
    while (value < x) {
        value *= 2;
        ++log;
    }
    return log;
}

void process_one() {
    int count;
    cin >> count;
    for (;count != 0; --count) {

        cout << count;
    }
}
/*
int some() {
    cout << "Hello world!" << endl;
    some();
    cout << sizeof(int) << sizeof(long) << sizeof(char) << endl;
    char c = -2;
    unsigned char uc = -2;
    double f = 1.2;
    cout << (int)c << (int)uc << "  " << f << "  " << int(f) << endl;
    cout << 'a' << 12311111111L << -23UL << 3.2E-10 << ' ' << (false) << true;
    string s;
    int a = 2;
    int b = 3;
    b = a+++b;
    cout << a << b << endl;
    a = a++ ;
    cout << a << true == 0;
    {
        int a = 1111;
    }
    cout << a;
    do { } while (0);
    // cin >> a;
    cout << a;
    char z;
    cin.get(z);
    cin.get(z);
    cout << z;
    //stack array
    int a[3] = {1, 2, 3};
    show_array(a, 3);
    rotate(a, 3, 2);
    show_array(a, 3);
    a[0] = true?100:1/0;
    show_array(a, 3);
    int cc = 4; int r = 0;
    MAX(b+2, cc+=4, r);
    cout << r << sqrt(2) << endl;
    sq_root_equasion(1, 4, 4);
    cout << '|' << log_int(5) << ' ' << log_int(11539);
    //process_one();
}*/
// TODO array cmp array
void one() { int a; cout << a; }
void tw() { int a = 321; }
void not_init_on_stack_get_prev_value() {
    one();
    tw();
    one();
}

void injected() {
    cout << "success injected! buf over!";
}

void inject() {
    int *m[1];
    m[3] = (int *) &injected;
}

long factorial(int n) {
    if (n < 2) return 1;
    return factorial(n - 1) * n;
}

int gcd_implementation(int a, int b) {
    if (b == 0) return a;
    return gcd_implementation(b, a % b);
}

int gcd(int a, int b) {
    if (a > b) return gcd_implementation(a, b);
    return gcd_implementation(b, a);
}

void revout(int x) {
    if (x == 0) {
        cout << endl;
        return;
    }
    int y = 0;
    cin >> y;
    revout(y);
    cout << x << ' ';
}

void reverese_output() {
    int x = 0;
    cin >> x;
    revout(x);
}

int main() {
    reverese_output();
    return 0;
}
