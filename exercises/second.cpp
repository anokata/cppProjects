#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
using namespace std;

struct String {

	String(const char *str = "") {
        size = strlen(str);
        this->str = new char [size + 1];
        strcpy(this->str, str);
    }

    String(size_t n, char c);

    ~String() {
        delete [] str;
    }

    void append(String &other);

	size_t size;
	char *str;
};

String::String(size_t n, char c) {
    size = n;
    str = new char [n + 1];
    for (int i = 0; i < n; i++) {
        str[i] = c;
    }
    str[n] = 0;
}

void String::append(String &other) {
    char * new_str = new char [size + other.size + 1];
    strcpy(new_str, str);
    strcpy(new_str + size, other.str);
    delete [] str;
    str = new_str;
    size = size + other.size;
}

int main() {
    String s("abc");
    cout << s.size << ' ' << s.str << ' ';
    String ss(3, 's');
    cout << ss.str << endl;
    s.append(ss);
    cout << s.str << s.size << endl;
    s.append(s);
    cout << s.str << s.size << endl;
    return 0;
}
