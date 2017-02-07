#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
using namespace std;
    //есть константные объекты - у них можно вызвать только конст методы.
    //mutable поля можно менять внутри const методов.

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

    void append(const String &other);
    //константный метод
    size_t _size() const {
        return size;
    }

    char &get(size_t pos);
    size_t length();
    bool equal(const String &other);

	char *str;
private:
	size_t size;
};

String::String(size_t n, char c) {
    size = n;
    str = new char [n + 1];
    for (int i = 0; i < n; i++) {
        str[i] = c;
    }
    str[n] = 0;
}

void String::append(const String &other) {
    char * new_str = new char [size + other.size + 1];
    strcpy(new_str, str);
    strcpy(new_str + size, other.str);
    delete [] str;
    str = new_str;
    size = size + other.size;
}

size_t String::length() {
    return size;
}

char & String::get(size_t pos) {
    return this->str[pos];
}

bool String::equal(const String &other) {
    if (this->size != other.size) return false;
    for (int i = 0; i < size; ++i) {
        if (str[i] != other.str[i]) return false;
    }
    return true;
}

int main() {
    String s("abc");
    cout << s.length() << ' ' << s.str << ' ';
    String ss(3, 's');
    cout << ss.str << endl;
    s.append(ss);
    cout << s.str << s.length() << endl;
    s.append(s);
    cout << s.str << s.length() << endl;
    int a = 32;
    // указатель на константу
    int const * p1;
    const int * p2;
    p1 = &a;
    p2 = &a;
    // константный указатель
    int * const p3 = &a;
    *p3 = 33;
    // константный указатель на константу
    int const * const p4 = &a;
    // const делает константным тип слева от него.
    //
    s.get(1) = 'Z';
    cout << s.str << ' ' << s.equal(s) << s.equal(ss) << endl;
    String z1 = "abc";
    String z2 = "abC";
    cout << z2.equal(z1);
    return 0;
}
