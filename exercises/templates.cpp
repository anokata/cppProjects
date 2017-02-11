#include <iostream>
#include <array>
using namespace std;

//Array<int> a;

template <typename T>
T sum(T a, T b) {
    cout << sizeof(T) << ')' << a << " + " << b << endl;
    return a + b;
}
template <typename T, typename R>
T sum(T a, R b) {
    cout << sizeof(T) << sizeof(R) << ')' << a << " + " << b << endl;
    return a + b;
}
template <typename T>
void print(T x) {
    static int count = 0;
    cout << x << ' ';
    ++count;
    if (count > 5) {
        cout << endl;
        count = 0;
    }
}

template <typename T, typename U>
void copy_n(T *dest, U *source, int size) {
    for (int i = 0; i < size; ++i) {
        *dest = (T)*source;
        dest++;
        source++;
    }
}

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };

/*
template <typename T>
T minimum(Array<T> a) {
    return a[0];
}
*/

int main() {
    auto x1 = sum(1, 2);
    auto x2 = sum(1.0, 2.0);
    auto x3 = sum(1, 2.0);
    print(1);
    print(1.0);
    print('c');
    print("str");
    print(true);
    print(123133);
    print("dffjdf");
    print(1);
    print(1);
    print(1);
    print(2);
    print(2);
    print<double>(2);
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4);
    cout << doubles[0] << doubles[1] << doubles[3];
    /*
Array<int> ints(3);
ints[0] = 10;
ints[1] = 2;
ints[2] = 15;
int min = minimum(ints, less); // в min должно попасть число 2
int max = minimum(ints, Greater()); // в max должно попасть число 15
*/
    cout << "end\n";
    return 0;
}
