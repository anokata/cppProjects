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

    operator char const *() const { // Оператор приведения к char const *
        cout << "Type String Cast to char const *\n";
        return str;
    }

    String &sliceFrom(int idx) {
        int newsize = size - idx;
        char * newmem = new char [newsize + 1]; // for \0
        size = newsize;
        for (int i = 0; i < size; ++i) {
            newmem[i] = str[i + idx];
        }
        //delete [] str;
        str = newmem;
    }

    String &sliceTo(int idx) {
        int newsize = idx; // 0?
        char * newmem = new char [newsize + 1];
        size = newsize;
        for (int i = 0; i < size; ++i) {
            newmem[i] = str[i];
        }
        newmem[idx - 1] = 0;
        //delete [] str;
        str = newmem;
    }

    /*String & operator[] (int idx) {
        cout << "non const";
        if (!slice) {
            slice = true;
            slc = idx;
            return *this;
        } else {
            sliceFrom(slc);
            sliceTo(idx);
            slice = false;
            return *this;
        }
    }*/

    String & operator[] (int idx) const {
        String *s = new String(this->str); // создать новую строку на основе данных текуще
        if (this->slice) {
            s->sliceTo(idx);
            s->slice = false;
        } else {
            s->sliceFrom(idx);
            s->slice = true;
        }
        return *s; // вернуть ссылку на эту строку
    }

	char *str;
private:
    bool slice = false;
    int slc = 0;
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

ostream& operator<<(ostream &os, String const &b) {
    const char *start = "\033[1;31m";
    const char *end = "\033[0m\n";
    os << start << '[' << b.str << ']' << end;
    return os;
}

void string_test(int deftest=13) {
    int i = 1;
    int k = i++ + i++ + i++; // k = 1 + 2 + 3
    cout << i << ' ' << k; // !!! 4 and 6
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
    cout << s; // operator<<
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
    String aaa = "bcd";
    cout << aaa;
    const char *bbb = aaa;
}

int counter(int init = 0) {
    static int c = init; // инициализация выполняется только один раз, при первом вызове
    cout << c << ' ' << init << endl;
    return ++c;
}

void static_test() {
    counter();
    counter();
    counter(20);
    counter();
}

struct Rational
{
    Rational(int numerator = 0, int denominator = 1) 
        : numerator_(numerator), denominator_(denominator) {}

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg() {};
    void inv();
    double to_double() const;

    Rational &operator+=(Rational rational) {
        add(rational);
        return *this;
    }
    Rational &operator-=(Rational rational) {
        sub(rational);
        return *this;
    }
    Rational &operator*=(Rational rational) {
        mul(rational);
        return *this;
    }
    Rational &operator/=(Rational rational) {
        div(rational);
        return *this;
    }
    int get_num() const  { return numerator_; }
    int get_den() const  { return denominator_; }
    explicit operator double () const { return to_double(); } 

private:
    int numerator_;
    int denominator_;
};

Rational operator+(Rational r1, Rational const & r2) {
    return r1 += r2;
}
Rational operator-(Rational r1, Rational const & r2) {
    return r1 -= r2;
}
Rational operator*(Rational r1, Rational const & r2) {
    return r1 *= r2;
}
Rational operator/(Rational r1, Rational const & r2) {
    return r1 /= r2;
}
Rational operator+(Rational r) {
    return r;
}
Rational operator-(Rational r) {
    return r = 0 - r;
}

double Rational::to_double() const {
    return (double) numerator_ / denominator_;
}
void Rational::inv() {
    numerator_ = -numerator_;
}
void Rational::add(Rational rational) {
    numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
    denominator_ *= rational.denominator_;
}
void Rational::sub(Rational rational) {
    numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
    denominator_ *= rational.denominator_;
}

void Rational::mul(Rational rational) {
    numerator_ *= rational.numerator_;
    denominator_ *= rational.denominator_;
}

void Rational::div(Rational rational) {
    numerator_ *= rational.denominator_;
    denominator_ *= rational.numerator_;
}

bool operator==(Rational r1, Rational const &r2) {
    return (r1.get_num() == r2.get_num()) && (r1.get_den() == r2.get_den());
}
bool operator!=(Rational r1, Rational const &r2) {
    return !(r1 == r2);
}
bool operator<(Rational r1, Rational const &r2) {
    return (r1.get_num() * r2.get_den() - r1.get_den() * r2.get_num()) < 0;
}
bool operator>(Rational r1, Rational const &r2) {
    return (r2 < r1);
}
bool operator>=(Rational r1, Rational const &r2) {
    return !(r1 < r2);
}
bool operator<=(Rational r1, Rational const &r2) {
    return !(r1 > r2);
}

int main() {
    cout << "Begin\n";
    Rational a(1, 2);
    cout << a.to_double() << endl;
    a.inv();
    cout << a.to_double() << endl;
    a += 2;
    a = a + 1;
    a = 10 - a;
    cout << (-a).to_double() << endl;
    cout << (2 == a);
    cout << (a == a);
    cout << (a < a);
    cout << (a < 2);
    cout << (a < 20);
    //SmartPtr a;
    //static_test();
    cout << endl;
    String s1 = "abcdefg123";
    cout << s1 ;
    s1.sliceFrom(2);
    cout << s1 ;
    s1.sliceTo(2);
    cout << s1 ;
    String s2 = "abcdefg123";
    cout << s2 ;
    //s2[1][3];
    s2[1][5];
    cout << s2;

    String const hello("hello");
    String const h("xddd");
    //cout << hello << hello[0] << hello[1] << hello[2] << hello[3] << hello[4];
    String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
    cout << hell << endl;
    String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
    cout << ell << endl;
    String const el  = hello[1][1]; // ==
    cout << el << endl;
    String const hhh("xx");
    cout << hhh << hhh[0][1];
    //String const hh("xx");


    cout << "End\n";
    return 0;
}
