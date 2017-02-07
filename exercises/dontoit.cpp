#include <iostream>
using namespace std;

 struct Cls {
 Cls(char c, double d, int i) : c(c), d(d), i(i) {};
 private:
     char c;
     double d;
     int i;
 };

struct hack {
     char c;
     double d;
     int i;
};

char &get_c(Cls &cls) {
    char *h = (char *) &cls;
    return *h;
}

double &get_d(Cls &cls) {
    hack *h = (hack *) &cls;
    return h->d;
}

int &get_i(Cls &cls) {
    hack *h = (hack *) &cls;
    return h->i;
} 

int main() {
    cout << "begin" << endl;

    Cls c('a', 2.0, 3);
    cout << get_c(c);
    get_c(c) = 'b';
    cout << get_c(c);

    cout << ' ' << get_d(c);
    get_d(c) = 3.1415926;
    cout << ' ' << get_d(c);

    cout << ' ' << get_i(c);
    get_i(c) = 30;
    cout << ' ' << get_i(c);

    cout << "end" << endl;
}
