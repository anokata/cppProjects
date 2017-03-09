#include <iostream>
#include <cmath>
using namespace std;

string rots(string s, int start) {
    char c = s[start];
    for (int i = start; i < s.size() - 1; ++i) {
        s[i] = s[i+1];
    }
    s[s.size() - 1] = c;
    return s;
}

int main() {
    cout << rots("some", 1);
    long double d;
    //cin >> d;
    //cout << sqrt(d);
    return 0;
}
