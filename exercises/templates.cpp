#include <iostream>
using namespace std;

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

int main() {
    auto x1 = sum(1, 2);
    auto x2 = sum(1.0, 2.0);
    auto x3 = sum(1, 2.0);
    cout << "end\n";
    return 0;
}
