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

    String(const String &s)
        : size(s.size), str(new char[size + 1]) // init list
    { // конструктор копирования. когда нужно создать на основе.
        cout << "Copy constructor\n";
        for (int i = 0; i <= size; i++) {
            str[i] = s.str[i];
        }
    }
    // virtual методы - разрешаются динамически при исполнении.
    // если есть указатель на переменную производного класса(указатель базового класса)
    // то при вызове вирутального метода вызовется метод производного класса.
    // виртуальный деструктор нужен для того чтобы можно было безопасно работать
    // с объектом через указатель на него с типом базового класса. и будет
    // вызван деструктор производного класса, чтобы правильно освободить ресуры.
    // вирт методы вообще предполагают обращение к методам через ссылку на объект произв.
    // классa (типа базового, но объект по ссылке - произодный может быть)

    String & operator=(String const & a) { // оператор присваивания.
        // разрушить дин данные и создать по аргументу новые\скопировать.
        if (this != &a) {
            cout << "Кроме себя.\n";
        }
        if (this != &a) {
            delete [] str;
            size = a.size;
            str = new char[size + 1];
            for (int i = 0; i <= size; i++) {
                str[i] = a.str[i];
            }
        }
        cout << "EQ = operator \n";
        return *this;
    }

    void append(const String &other);
    //константный метод
    size_t _size() const {
        return size;
    }

    char &get(size_t pos);
    size_t length();
    bool equal(const String &other);
    char & at(size_t idx) { 
        cout << "&char\n";
        return str[idx]; }
    char at(size_t idx) const { 
        cout << "const char\n";
        return str[idx]; }

	char *str;
private:
	size_t size;
};

struct ChildString : public String { // публичное наследование.
    void append(int i); // перегрузка
    using String::append; // чтобы не переопределить а перегрузить.
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

void test_fun_copy_const(String a) {

}

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};
void foo_says(const Foo& foo) { foo.say(); }

struct FooOpened : Foo {
    FooOpened(const char *m) : Foo(m) {};
};
const Foo get_foo(const char *msg) {
    FooOpened f(msg);
    return f;
}

void overloaded(int i) {
    cout << "Over INT " << i << endl;
}
void overloaded(double i) {
    cout << "Over double " << i << endl;
}
void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }

#include <chrono>
#include <thread>
void updated_message(int n) {
    cout << "Progress:" << endl;
    for (int i = 0; i < n; i++) { // repeatn(fun, n) , void fun(int n); TODO
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << "\r some [%" << i << "] mesage    ";
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "\033[1;31mbold red text\033[0m\n";
}

int main() {
    updated_message(10);
    foo('a');
    overloaded(2.3);
    const char * msg = "HI!\n";
    foo_says(get_foo(msg));
    String s("abc");
    char c82 = s.at(0); // зависит только от того константный объект или нет?
    cout << c82 << endl;
    c82 = 'A';
    cout << c82 << endl;
    String const conss("HABUDABI");
    char const &ch2 = conss.at(0);
    cout << ch2 << endl;
    c82 = 'h'; // not work;
    cout << ch2 << endl;
    cout << s.length() << ' ' << s.str << ' ';
    String ss(3, 's');
    cout << ss.str << endl;
    s.append(ss);
    cout << s.str << s.length() << endl;
    s.append(s);
    cout << s.str << s.length() << endl;
    String copy = s; // тут вызовется конст. копирования.
    cout << "copy=" << copy.str << endl;
    test_fun_copy_const(s); // и тут тоже 
    s = s; // вызовется оператор =
    cout << "before op= " << s.str << ' ';
    s = ss; // вызовется оператор =
    cout << "after op= " << s.str << endl;
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
