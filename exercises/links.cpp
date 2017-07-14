#include <iostream>

class A;
class B;

class B {
    public:
        B() {}
        int x;
};

class A {
    public:
        A() : b(B()) {
            /* this->b = new B(); */
            //this->b = B();
        }
        const B &b;
};


int main() {
    std::cout << "\033;hi\n";
    /* A a; */
    /* A &l = A(); */
    int x;
    std::string z = "abc";
    std::string &y = z;
    std::pair<int, int> a;
    const std::pair<int, int> &b = std::make_pair<int, int>(1,2);
    return 0;
}
