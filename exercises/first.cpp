#include <iostream>
#include <set>
#include <map>
#include <cassert>
#include <iomanip>
#include <utility> // pair ?
#include <cmath>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream>

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


bool isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

char toUpper(char c) {
    if (isLower(c)) {
        return (c - 'a') + 'A';
    }
    return c;
}

char toLower(char c) {
    if (isUpper(c)) {
        return (c - 'A') + 'a';
    }
    return c;
}

char changeCase(char c) {
    if (isLower(c)) {
        return toUpper(c);
    } else {
        return toLower(c);
    }
}

void strings_0() {
    string s = "abc";
    s[1] = 'g';
    cout << s << endl;
    //cin >> s;
    cout << ">>" + s + "<<" << sizeof(s) << endl;
    //cout << &s << ' ' << *(&s + 1);
    getline(cin, s);
    cout << s.size() << ' ' << (unsigned)s[0] << endl;
    for (auto c : s) {
        if (c != ' ') {
            if (c >= '0' && c <= '9') cout << c;
        } else {
            cout << '_';
        }
    }
    bool bbb = s.find("asa") != -1;
    cout << endl << s << endl << bbb;
}

int word_count(string s) {
    int count = 1;
    for (char c : s) {
        if (c == ' ') ++count;
    }
    return count;
}

bool is_palindrom(string s) {
    int len = s.size();
    for (int i = 0; i < len/2; ++i) {
        if (s[i] != s[len-i-1]) return false;
    }
    return true;
}

void test_palindrom() {
    string str;
    getline(cin, str);
    if (is_palindrom(str)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}

string longest_word_one_space(string s) {
    int word_start = 0;
    int word_end;
    int len = s.size();
    word_end = s.find(' ');
    string str;
    int max_start = 0;
    int max_end = 0;
    int max_len = 0;

    while (word_end != -1) {
        if (max_len < (word_end - word_start)) {
            max_len = word_end - word_start;
            max_start = word_start;
            max_end = word_end;
        }
        word_start = s.find(' ', word_end + 1);
        word_end = s.find(' ', word_start + 1);
    }
    if (max_start == 0) {
        str = s.substr(max_start, max_len);
    } else {
        str = s.substr(max_start + 1, max_len - 1);
    }
    cout << '"' << str << '"';
    return str;
}

string longest_word_1s_simple(string s) {
    int max_start = 0;
    int max_len = 0;
    int word_start = 0;
    int word_len = 0;
    bool word = true;

    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c != ' ') {
            if (word) {
                word_len++;
            } else {
                word = true;
                word_start = i;
                word_len = 0;
            }
        } else {
            if (word) {
                word = false;
                if (max_len < word_len) {
                    max_len = word_len;
                    max_start = word_start;
                    word_len = 0;
                }
            }
        }
    }

    if (max_len < word_len) {
        max_len = word_len;
        max_start = word_start;
    }

    string str;
    if (max_start == 0) {
        str = s.substr(max_start, max_len);
    } else {
        str = s.substr(max_start, max_len + 1);
    }
    cout << '"' << str << '"' << endl;
    return str;
}

bool is_num_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool is_correct_IP(string s) {
    if (s.size() < 7) return false; // min addr '0.0.0.0'
    char c = '\0';
    int num = 0;
    int dot_count = 0;
    string number = "";
    if (!is_num_digit(s[0])) return false;
    for (int i = 0; i < s.size(); ++i) {
        c = s[i];
        if (is_num_digit(c)) {
            number += c;
        } else if (c == '.') {
            dot_count++;
            if (dot_count > 3) return false;
            if (number.size() == 0) return false;
            num = stoi(number);
            if (num < 0 || num > 255) return false;
            number = "";
        } else return false;
    }
    if (dot_count != 3) return false;
    if (c == '.') return false;
    num = stoi(number);
    if (num < 0 || num > 255) return false;
    return true;
}

void test_IP(string ip) {
    if (is_correct_IP(ip)) {
        cout << "YES" << endl;
    } else cout << "NO" << endl;
}

void str_tests() {
    string s = "abc";
    cout << s.find('a') << ' ' << s.find('c');
    //cout << longest_word_one_space("abccc abc abcd ab abc");
    longest_word_1s_simple("abccc abc abcd ab abc");
    longest_word_1s_simple("a1 abcd a2");
    longest_word_1s_simple("ab abc abcd ab abc123123");
    cout << stoi("123") << endl;
    test_IP("127.12..123");
}

void set_test() {
    set<int> s;
    s.insert(22);
    s.insert(22);
    s.insert(2);
    s.insert(-2);
    cout << (s.find(1) == s.end()) << endl;
    cout << (s.find(2) == s.end()) << endl;
    s.erase(2);
    cout << (s.find(2) == s.end()) << endl;
    for (int x : s) {
        cout << x << ',';
    }
    cout << "SIZE:" << s.size() << endl;
    multiset<char> m;
    m.insert('a');
    m.insert('b');
    m.insert('b');
    m.insert('a');
    m.insert('e');
    m.insert('a');
    m.insert('a');
    m.insert('b');
    m.insert('c');
    m.insert('z');
    for (auto x : m) cout << x << ' ';
    int count = 0;
    for (auto now = m.lower_bound('b'); now != m.upper_bound('b'); now++) {
        count++;
    }
    cout << "\n b in set:" << count;
}

void map_test() {
    map<char, string> m;
    m['d'] = "dom";
    m['d'] = "domd";
    m['A'] = "ENter";
    m['{'] = "s:{NN:'sss'}";
    if (m.find('d') != m.end()) cout << "exist\n";
    for (auto x : m) {
        cout << x.first << ':' << x.second << endl;
    }
}

set<int> input_numbers() {
    int n = 0;
    cin >> n;
    set<int> numbers;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        numbers.insert(x);
    }
    return numbers;
}

int uniq_numbers() {
    auto nums = input_numbers();
    return nums.size();
}

void exist_test() {
    int n = 0;
    cin >> n;
    set<int> nums;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (nums.find(x) != nums.end()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        nums.insert(x);
    }
}

set<int> set_intersect(set<int> s1, set<int> s2) {
    set<int> result;
    for (auto x : s1) {
        if (s2.find(x) != s2.end()) {
            result.insert(x);
        }
    }
    return result;
}

int intersected_sets() {
    auto nums1 = input_numbers();
    auto nums2 = input_numbers();
    auto isect = set_intersect(nums1, nums2);
    return isect.size();
}

void time_sec() {
    int n;
    cin >> n;
    n = n % (60 * 60 * 24);
    int hours = n / (60 * 60);
    int minuts = (n - hours * 60 * 60) / 60;
    int d_mins = minuts / 10;
    int e_mins = minuts % 10;
    int seconds = (n - hours * 60 * 60) % 60;
    int d_sec = seconds / 10;
    int e_sec = seconds % 10;
    cout << hours << ':' << d_mins << e_mins << ':' << d_sec << e_sec;
}

int mkad(int v, int t) {
    int s = v * t;
    int end = s % 109;
    int z = s / 109;
    //int abs_z = (z * z) / z;
    cout << end << ' ' << z << ' ' << 109 + end << endl;
}

int snail(int h, int a, int b) {
    int d = a - b;
    int had = (h - a) / d;
    int s = (h - a) / d + 1;
    int aab = a / d;
    int hd = h / d;
    int db = d / b;
    int p = hd - (a / h);
     int k = h % d;
     int kk = (h - a) % d;

    cout << "snail " << s << " k= " << k << " hd= " << hd << " p= " << p << " kk= " << kk << endl;
    return s;
}

void snail_test() {
    assert(snail(2, 3, 1) == 1);
    assert(snail(2, 2, 1) == 1);
    assert(snail(3, 2, 1) == 2);
    assert(snail(4, 2, 1) == 3);
    assert(snail(5, 2, 1) == 4);
    assert(snail(3, 3, 1) == 1);
    assert(snail(4, 3, 1) == 2);
}

void king_move() {
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    int dx = sx - ex;
    int dy = sy - ey;
    cout << dx << ' ' << dy;
    if ((dx * dx) < 2 && (dy * dy) < 2) {
        cout << "YES";   
    } else {
        cout << "NO";
    }
}

void horse_move() {
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    int dx = sx - ex;
    int dy = sy - ey;
    dx = dx * dx;
    dy = dy * dy;
    if ((dx == 4 && dy == 1) || (dx == 1 && dy == 4)) {
        cout << "YES";   
    } else {
        cout << "NO";
    }
}

void ferz_move() {
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    int dx = sx - ex;
    int dy = sy - ey;

    if (((dx * dx) == (dy * dy)) || (sx == ex || sy == ey)) {
        cout << "YES";   
    } else {
        cout << "NO";
    }
}

void strcat(char *to, const char *from)
{
    // first go to end
    while (*to) ++to;
    // copy
    while (*from) {
        *to = *from;
        from++;
        to++;
    }
    *to = *from;
}

int strstr(const char *text, const char *pattern)
{
    if (*pattern == 0) return 0;
    if (*text == 0) return -1;
    int ppos;
    for (int pos = 0; text[pos]; ++pos) {
        for (ppos = 0; pattern[ppos]; ++ppos) {
            // cout << text[pos + ppos] << '=' << pattern[ppos] << ' ' << pos << ' ' << ppos;
            if (text[pos + ppos] != pattern[ppos]) {
                break;
            }
        }
        if (pattern[ppos] == 0)
            return pos;
    }
    return -1;
}
//strstr, strncat, strlen <cstring>
// max_element

void strstr_test() {
    const char *s1 = "";
    const char *s2 = "abc";
    const char *s3 = "a";
    const char *s4 = "b";
    const char *s5 = "c";
    const char *s6 = "ccc";
    const char *s7 = "ccd";
    const char *s8 = "cd";
    const char *s9 = "abc def gef";
    const char *s0 = "def";
    cout << strstr(s2, s1) << endl;
    cout << strstr(s2, s3) << endl;
    cout << strstr(s2, s4) << endl;
    cout << strstr(s2, s5) << endl;
    cout << strstr(s6, s4) << endl;
    cout << strstr(s7, s7) << endl;
    cout << strstr(s9, s0) << endl;
    cout << strstr(s0, s9) << endl;
}

void sort_test() {
    char s[5] = "gwba";
    cout << s << endl;
    sort(s, s+5);
    cout << s+1 << '.' << (int)s[0] << (int)s[1] << endl;
    int a[5] = {3, 2, 1, 5, 4};
    show_array(a, sizeof(a)/sizeof(int));
    sort(a, a+5);
    show_array(a, 5);
}

void swap_link(int &a, int &b) {
    int t = b;
    b = a;
    a = t;
}
/* у ссыки нет нулевого значения. ссылка обязана быть инициализирована. ссылку нельзя
 * переприсвоить. её не надо разыменовывать. с её адресом ничего не сделать. 
 * нельзя взять адресс самой ссылки(получить арес переменной на которую ссылается
 * . нельзя делать ссылки на ссылки. нет арифметики
 * ссылок. не сделать массив ссылок.*/
// Указатели и ссылки могут быть только на lvalue
void test_swapl() {
    int a = 10, b = 20, c = 15;
    int & s = a;
    swap_link(c, s);
    cout << a << ' ' << b << ' ' << c << endl;
    swap_link(a, b);
    cout << a << ' ' << b << ' ' << c << endl;
    swap_link(c, b);
    cout << a << ' ' << b << ' ' << c << endl;
    int m[3] = {1,2,3};
    int &d = *m; // ссылка должна быть на значение а не на адрес.
    d = 4; // а так как это ссылка то это не копия значения и его можно менять в том объекте.
    show_array(m, 3);
    int &l = (a > b ? a : ++b);
    cout << b << '_';
    ++b = b;
    cout << b; 
    // есть ли смысл возвращать ссылку функцией? да если это выделенная память а не стек
    // аргумент ссылка на массив - int (&a)[3]
    // для больших объектов аргументов лучше (для избегания копирования) передвать по
    // type const &name например string const &str
    // ссылка на указатель
    int *pl = &a;
    int *(&pla) = pl;
    cout << endl << "pla " << pla << "val " << *pla << endl;
}

void dynamic_mem_cpp() {
    int *pint = new int;
    cout << *pint << ' ';
    *pint = 42;
    cout << *pint << ' ';
    delete pint;
    pint = 0;
    //cout << *pint << '*' << pint << ' ';
    pint = new int(128);
    cout << *pint << ' ' << endl;
    delete pint;
    pint = 0;

    long *plong = new long[10];
    cout << plong[1] << ' ';
    plong[1] += 21;
    cout << plong[1] << ' ';
    delete [] plong;
    plong = 0;
    //cout << plong[1] << ' ';

}


char *resize(const char *str, unsigned size, unsigned new_size) {
    char *newmem = new char[new_size];
    if (size > new_size) size = new_size;
    for (int i = 0; i < size; ++i) {
        newmem[i] = str[i];
    }
    delete [] str;
    return newmem;
}

char *getline_() {
    char c;
    int size = 4;
    char *mem = new char[size];
    int len = 0;
    mem[len] = 0;

    while (cin.get(c)) {
        if (c == '\n') break;
        mem[len] = c;
        len++;
        if (len + 1 > size) {
            mem = resize(mem, size, size * 2);
            size *= 2;
        }
    }
    mem[len] = 0;
    return mem;
}

void resize_test() {
    int *ar = new int[3];
    ar[0] = 2;
    ar[1] = 1;
    ar[2] = 4;

    show_array(ar, 3);
    ar = (int *) resize((char *) ar, 3 * sizeof(int), 5);
    show_array(ar, 5);

    delete [] ar;
}

void getline_test() {
    char *line = getline_();
    cout << "line:>>>" << line << "<<<" << endl;
    delete [] line;
}

void second_max() {
    int x;
    cin >> x;
    int max = x;
    int last = 0;
  
    while (x != 0) {
        cin >> x;
        if (max < x) {
            last = max;
            max = x;
        } else if (last < x) {
            last = x;
        }
    }
    cout << last;
}

void rates_year() {
    int p, x, y, k;
    cin >> p >> x >> y >> k;
    int deposit;
    double rated;
    while (k != 0) {
        deposit = x * 100 + y;
        rated = deposit * (100 + p) / 100.0;
        x = rated / 100;
        y = rated - x * 100;
        k--;
    }
    
    cout << x << ' ' << y;
    return;
}

void avg_inputed() {
    int x;
    cin >> x;
    double avg = 0;
    int sum = 0;
    int count = 0;
    while (x != 0) {
        sum += x;
        count++;
        cin >> x;
    }
    avg = sum / (double)count;
    cout << fixed << setprecision(11) << avg;
}

long line_fibo() {
    int n;
    cin >> n;
    if (n == 0 || n == 1) {
        cout << n;
        return 0;
    }
    long f_pred = 1;
    long f_ppred = 0;
    long f = 0;
    while (n != 1) {
        n--;
        f = f_ppred + f_pred;
        f_ppred = f_pred;
        f_pred = f;
    }
    cout << f;
    return 0;
}

int where_fibo() {
    long a;
    cin >> a;
    if (a == 0 || a == 1) {
        cout << a;
        return 0;
    }
    long f_pred = 1;
    long f_ppred = 0;
    long f = 0;
    int n = 1;
    while (a > f) {
        n++;
        f = f_ppred + f_pred;
        f_ppred = f_pred;
        f_pred = f;
    }
    if (a == f) {
        cout << n;
    } else {
        cout << -1;
    }
    return 0;
}

void vector_sort() {
    vector <int> b(3);
    b[0]=3; b[1]=2; b[2]=1;
    for (auto x : b) cout << x << ' ';
    sort(b.begin(), b.end());
    cout << endl;
    for (auto x : b) cout << x << ' ';

    vector <pair <int, int>> a(3);
    a[0] = {20, 1};
    a[1] = {12, 2};
    a[2] = {10, 3};
    for (auto x : a) cout << x.second << ' ';
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    cout << endl;
    for (auto x : a) cout << x.second << ' ';
}
    // cout << fixed << setprecision(1) << 32.12 << ' ' << 21 << ' ' << trunc(123.123) << endl;
    // cout << floor(2.9) << ' ' << ceil(2.1) << ' ' << round(2.5);
    // int m[10]; for (auto x : m) cout << x;

struct man {
    int len;
    string name;
};

bool cmp_man(man a, man b) {
    return a.len < b.len;
}

void struct_vec_sort_and_permut() {
    vector <man> c(3);
    c[0] = {4, "abc"};
    c[1] = {3, "sonya"};
    c[2] = {5, "kiri"};
    cout << endl;
    for (auto x : c) cout << x.len << ':' << x.name << ' ';
    sort(c.begin(), c.end(), cmp_man);
    cout << endl;
    for (auto x : c) cout << x.len << ':' << x.name << ' ';
    while (next_permutation(c.begin(), c.end(), cmp_man)) {
        cout << endl;
        for (auto x : c) cout << x.len << ':' << x.name << ' ';
    }
    cout << 'B' << ("ab" > "aa");
}

void sort_inputed_array() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}

void shoes3() {
    int n;
    int foot;
    cin >> foot >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int last = foot;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= last) {
            cnt++;
            last = a[i] + 3;
        }
    }
    cout << cnt;
}

struct member {
    int id;
    int score;
};

bool cmp_olimp(member a, member b) {
    if (a.score < b.score) {
        return false;
    } else if (a.score > b.score) {
        return true;
    } else return a.id < b.id;
}

void inputed_struct_sort_rev() {
    int n;
    cin >> n;
    vector <member> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].id >> a[i].score;
    }
    sort(a.begin(), a.end(), cmp_olimp);
    for (int i = 0; i < n; i++) {
        cout << a[i].id << ' ' << a[i].score << endl;
    }
}

struct point {
    int x;
    int y;
};

double distance0(point p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

bool cmp_point(point a, point b) {
    return distance0(a) < distance0(b);
}

void points_sorted() {
    int n;
    cin >> n;
    vector <point> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end(), cmp_point);
    for (int i = 0; i < n; i++) {
        cout << a[i].x << ' ' << a[i].y << endl;
    }
}

struct student {
    string name;
    string surname;
    double avg_rank;
};

bool cmp_students(student a, student  b) {
    return a.avg_rank > b.avg_rank;
}

void students_sort_avg() {
    int n;
    cin >> n;
    vector <student> a(n);
    int m, p, f;
    for (int i = 0; i < n; i++) {
        cin >> a[i].surname >> a[i].name;
        cin >> m >> p >> f;
        a[i].avg_rank = (m + p + f) / 3.0;
    }
    stable_sort(a.begin(), a.end(), cmp_students);
    for (int i = 0; i < n; i++) {
        cout << a[i].surname << ' ' << a[i].name << endl;
    }
}

set<int> input_set() {
    int n;
    cin >> n;
    set <int> s;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        s.insert(x);
    }
    return s;
}

void print_int_set(set<int> s) {
    for (auto i : s) {
        cout << i << ' ';
    }
}

void two_lines() {
    set<int> s1 = input_set();
    set<int> s2 = input_set();
    set<int> s3 = set_intersect(s1, s2);
    print_int_set(s3);
}

map <string, string> input_string_dict() {
    map <string, string> d;
    int n;
    cin >> n;
    string s, k;
    for (int i = 0; i < n; i++) {
        cin >> s >> k;
        d[k] = s;
        d[s] = k;
    }
    return d;
}

int max_same() {
    int x;
    cin >> x;
    int longest = 1;
    int same = 0;
    int max = 1;
    while (x != 0) {
        cin >> same;
        if (x == same) {
            longest++;
            if (max < longest) {
                max = longest;
            }
        } else {
            longest = 1;
        }
        x = same;
    }
    cout << max;
}

int local_max_count() {
    int max = 0;
    int a, b, c;
    cin >> a;
    if (a == 0) return 0;
    cin >> b;
    if (b == 0) return 0;
    cin >> c;
    if (c == 0) return 0;

    while (c != 0) {
        if (b > a && b > c) {
            max++;
        }
        a = b;
        b = c;
        cin >> c;
    }
    return max;
}

int local_max_min_len() {
    int maxpos = 0;
    int mingap = 0;
    bool first = true;
    bool dual = false;
    int a, b, c;
    cin >> a;
    if (a == 0) return 0;
    cin >> b;
    if (b == 0) return 0;
    cin >> c;
    if (c == 0) return 0;

    while (c != 0) {
        if (first) {
            if (b > a && b > c) {
                first = false;
            }
        } else {
            if (b > a && b > c) {
                if (mingap == 0 || mingap > maxpos) {
                    mingap = maxpos;
                    dual = true;
                }
                maxpos = 0;
            } else {
                maxpos++;
            }
        }
        a = b;
        b = c;
        cin >> c;
    }
    if (dual) { 
        return mingap + 1;
    } else return 0;
}

double std_sigma() { // NOT YET
    int x;
    cin >> x;
    double s;
    while (x != 0) {

        cin >> x;
    }

    return s;
}

void filework() {
    char s[] = "1234";
    ofstream fout("out.txt");
    fout << "string '" << s << "' length= " << sizeof(s) << endl;
}

struct Point {
    int x;
    int y;
    const int z;
    double length_to_0(int r = 1);
    // initialization list !!! выполняется раньше и можно инициализовать константные поля.
    // порядок выполения инит x(?) y(?) зависит от порядка объявления полей.
    Point() : x(sqrt(2)), y(11), z(13) {
        cout << "From Point() constructor " << y << "\n";
    }
    Point(int zz) : z(zz*2) { // explicit чтобы запредить неявное преобразование при =
        x = zz;
        y = zz * 2;
        cout << "From Point(int) constructor(inplicit from = ?)\n";
    }
    Point(int a, int b) : z(113) {
        x = a;
        y = b;
        cout << "From Point(int, int) constructor\n";
    }
    ~Point() {
        cout << "destructor call " << x << "\n";
    }
};
//Placement new - new(pointer) Type;

double Point::length_to_0(int r) {
    return sqrt(this->x * x + y * y) * r;
}

typedef Point * pPoint;

struct TPoint{
    Point p;
    TPoint() {
        cout << "default constructor";
    }
    TPoint(int x) {
        cout << "not default constructor?";
    }

};

void struct_with_method() {
    pPoint p = new Point;
    p->x = 2; p->y = 3;
    cout << p->length_to_0();
    cout << endl << "------constructors-----" << endl;
    cout << "--pointer to *P\n";
    Point *a;
    cout << "--new it\n";
    a = new Point;
    cout << "--on stack P\n";
    Point b;
    cout << "--on stack P {init}\n";
    {
        Point bb = {1111, 2};
    }
    cout << "--on stack P(int)\n";
    Point c(29);
    cout << c.z << endl;
    cout << "--неявный вызов конструктора с одним аргументом при присваивании в объявлении.\n";
    Point cc = 30;
    Point ccc = {12};
    cout << "--on stack P(int, int)\n";
    Point d(29, 19);
    cout << "--on new P(int, int)\n";
    delete a;
    a = new Point(1, 3);
    delete a;
    cout << "Tpoint\n";
    TPoint t(2);
    TPoint r(); // !!! объявление фун
    TPoint rr; // вызов конструктора

}

int square_roots() {
    double a, b, c, d, x1, x2;
    //cin >> a >> b >> c;
    a = 0; b = 1; c = 1;
    if (a == 0 && b == 0 && c == 0) {
        cout << 3;
        return 0;
    } 
    if ((a == 0 && b == 0)) {
        cout << 0;
        return 0;
    } 
    if (b != 0 && a == 0 && c != 0) {
        x1 = -c / b;
        cout << 1 << ' ' << x1;
        return 0;
    } 
    if ((b != 0 && a == 0 && c == 0) || (b == 0 && c == 0 && a != 0)) {
        cout << 1 << ' ' << 0;
        return 0;
    }
    
    d = b * b - 4 * a * c;
    if (d > 0) {
        x1 = (-b + sqrt(d)) / (2 * a);
        x2 = (-b - sqrt(d)) / (2 * a);
        if (x1 < x2) {
            cout << 2 << ' ' << x1 << ' ' << x2;
        } else {
            cout << 2 << ' ' << x2 << ' ' << x1;
        }
    } else if (d == 0) {
        x1 = (-b + sqrt(d)) / (2 * a);
        cout << 1 << ' ' << x1;
    } else {
        cout << 0;   
    }
}

int kramer2() {
    double a, b, c, d, e, f;
    //cin >> a >> b >> c >> d >> e >> f;
    a = 1; b = 2; 
    c = 1; d = 1; 
    e = 1; f = 6;
    double dd, d1, d2, x, y;
    dd = a * d - b * c;
    d1 = e * d - f * b;
    d2 = a * f - c * e;
    cout << dd << ' ' << d1 << ' ' << d2 << endl;
    x = d1 / dd;
    y = d2 / dd;
    cout << x << ' ' << y;

}

void even_vector() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i += 2) {
        cout << a[i] << ' ';
    }
}

void even_elems() {
    int n;
    cin >> n;
    vector <int> a;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }
    for (int z : a) {
        if (z % 2 == 0) {
            cout << z << ' ';
        }
    }
}

void vector_pairsign() {
    int n;
    cin >> n;
    vector <int> a;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }
    for (int z = 1; z < n; z++) {
        if ((a[z] > 0 && a[z-1] > 0) || (a[z] <= 0 && a[z-1] <= 0)) {
            cout << a[z-1] << ' ' << a[z];
            break;
        }
    }
}

void vec_min() {
    int n;
    cin >> n;
    vector <int> a;
    int x, min;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }
    bool first = true;
    for (int i = 1; i < n; i++) {
        if (a[i] > 0 && first) {
            min = a[i];
            first = false;
        }
        if (a[i] > 0 && min > a[i]) {
            min = a[i];
        }
    }
    cout << min;
}

int min_even() {
    int n;
    cin >> n;
    bool is_even = false;
    int min;
    int x, absx;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (x == 0) continue;
        absx = abs(x);
        if (absx % 2 == 1 && !is_even) {
            is_even = true;
            min = x;
        } else if (absx % 2 == 1 && min > x) {
            min = x;
        }
    }
    if (!is_even) {
        cout << 0;
        return 0;
    } else {
        cout << min;
    }
}

int differ() {
    int n;
    cin >> n;
    long x;
    long prev = 0;
    long diff = 0;
    bool first = true;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (first) {
            diff++;
            prev = x;
            first = false;
            continue;
        }
        if (prev != x) {
            diff++;
        }
        prev = x;
    }
    cout << diff;
}

void swaped() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i += 2) {
        cout << a[i] << ' ' << a[i-1] << ' ';
    }
    if (n % 2 == 1) cout << a[n-1];
}

void shiftvec() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int succ = a[0];
    int t;
    for (int i = 1; i < n; ++i) {
        t = a[i];
        a[i] = succ;
        succ = t;
    }
    a[0] = succ;
    for (auto x : a) cout << x << ' ';
    cout << endl;
    int pairs = 0;
    for (int i = 0; i < n; ++i) {
        for (int k = i + 1; k < n; ++k) {
            if (a[i] == a[k]) pairs++;
        }
    }
    cout << pairs;
    cout << endl;
    for (int i = 0; i < n; ++i) {
        bool uniq = true;
        for (int k = 0; k < n; ++k) {
            if (i != k && a[i] == a[k]) uniq = false;
        }
        if (uniq) cout << a[i] << ' ';
    }
}

int ferz8() {
    vector <int> xs(8);
    vector <int> ys(8);
    for (int i = 0; i < 8; ++i) {
        cin >> xs[i];
        cin >> ys[i];
    }
    int dx, dy;
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            if (xs[i] == xs[j] || ys[i] == ys[j]) {
                cout << "YES";
                return 0;
            }
            dx = xs[i] - xs[j];
            dy = ys[i] - ys[j];
            dx *= dx;
            dy *= dy;
            if (dx == dy) {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}

int kegleball() {
    int balls, pins;
    cin >> pins >> balls; 
    vector <bool> a(pins);
    for (int i = 0; i < pins; i++) {
        a[i] = true;
    }
    int l, r;
    for (int i = 0; i < balls; i++) {
        cin >> l >> r;
        for (int k = l; k <= r; k++) {
            a[k-1] = false;
        }
    }

    for (bool x : a) {
        if (x) {
            cout << 'I';
        } else {
            cout << '.';
        }
    }
}

void show_2d_array(int a[][100], int rows, int cols) {
    cout << endl;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            cout << a[x][y] << ' ';
        }
        cout << endl;
    }
}

int arrays_2d() {
    int rows, cols;
    int array[100][100];
    cin >> rows >> cols;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            cin >> array[x][y];
        }
    }
    int max = array[0][0];
    int max_x = 0, max_y = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (array[x][y] > max) {
                max = array[x][y];
                max_x = x;
                max_y = y;
            }
        }
    }
    cout << max_x << ' ' << max_y;
    //show_2d_array(array, rows, cols);
}

int array2d_star() {
    int n;
    cin >> n;
    char a[15][15];
    int m = n / 2;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (y == m || x == m || x == y || x == n-y-1) {
                a[x][y] = '*';
            } else {
                a[x][y] = '.';
            }
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            cout << a[x][y] << ' ';
        }
        cout << endl;
    }
}

int array2d_diag1() {
    int n;
    cin >> n;
    int a[100][100];
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
                a[x][y] = abs(x-y);
        }
    }
    // output
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            cout << a[x][y] << ' ';
        }
        cout << endl;
    }
}

int array2d_swapCol() {
    int n, m;
    cin >> n >> m;
    int a[100][100];
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
                cin >> a[x][y];
        }
    }
    int sx, ex;
    cin >> sx >> ex;
    for (int x = 0; x < n; ++x) {
        int t = a[x][sx];
        a[x][sx] = a[x][ex];
        a[x][ex] = t;
    }
    // output
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cout << a[x][y] << ' ';
        }
        cout << endl;
    }
}

int array2d_is_symm() {
    int n;
    cin >> n;
    int a[10][10];
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
                cin >> a[x][y];
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (a[x][y] != a[y][x]) {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES";
}

int array2d_diagonals(int d = 0) {
    int n;
    cin >> n;
    //int a[10][10];
    int a[10][10] ={{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
                //cin >> a[x][y];
        }
    }
    int diag;
    cin >> diag;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if ((x-y) == diag) {
                cout << a[x][y] << ' ';
            }
        }
    }
}

int array2d_transpose() {
    int n, m;
    cin >> n >> m;
    //int a[10][10];
    int a[1000][1000] ={{11, 12, 13, 14},
                        {21, 22, 23, 24},
                        {31, 32, 33, 34}};
    int b[1000][1000];
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
                //cin >> a[x][y];
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            b[y][x] = a[x][y];
        }
    }
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
            cout << b[x][y] << ' ';
        }
        cout << endl;
    }
}

int array2d_findline() {
    int n, m;
    cin >> n >> m;
    //int a[20][20];
    int a[20][20] ={{0, 1, 0, 0},
                        {1, 0, 0, 0},
                        {0, 0, 0, 0}};
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
                //cin >> a[x][y];
        }
    }
    int k;
    cin >> k;
    int now = 0;
    for (int x = 0; x < n; ++x) {
        now = 0;
        for (int y = 0; y < m; ++y) {
            if (a[x][y] == 1) {
                now = 0;
            } else {
                ++now;
                if (now >= k) {
                    cout << x + 1;
                    return 0;
                }
            }
        }
    }
    cout << 0;
}

int array2d_rotate90() {
    int n, m;
    //cin >> n >> m;
    n=3;m=4;
    const int N = 100;
    int a[N][N] ={{11, 12, 13, 14},
                        {21, 22, 23, 24},
                        {31, 32, 33, 34}};
    int b[N][N];
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
                //cin >> a[x][y];
        }
    }
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
            //b[x][y] = a[y][m-x-1];
            b[x][y] = a[n-y-1][x];
        }
    }
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
            cout << b[x][y] << ' ';
        }
        cout << endl;
    }
}

int array2d_snake() {
    int n, m;
    cin >> n >> m;
    const int N = 30;
    int a[N][N];
    int i = 1;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (x % 2 == 1) {
                a[x][m-y-1] = i;
            } else {
                a[x][y] = i;
            }
            ++i;
        }
    }
    //other diag
    int y;
    i = 0;
    for (int s = 0; s < n*m; ++s) {
        for (int x = 0, y = s; x <= s && x < n; ++x, --y) {
                //cout << x << ':' << y << ' ';
                //a[x][y] = ++i;
        }
        cout << endl;
    }
    i = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if ((x + y) % 2 == 1) {
                a[x][y] = 0;
            } else {
                a[x][y] = ++i;
            }
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cout << setw(4) << a[x][y];
        }
        cout << endl;
    }
}

int array2d_spiral() {
    int n, m;
    cin >> n >> m;
    const int N = 100;
    int a[N][N];
    int i = 1;
    bool xy = true;
    bool ud = true;
    int x = 0;
    int y = 0;
    while (i <= n*m) {
        a[x][y] = i++;
        if (x >= m) {
            xy = !xy;
        }
        if (y >= n) {
            xy = !xy;
            ud = !ud;
        }
        if (x < 0) {
            xy = !xy;
            ud = !ud;
        }
        if (y < 0) {
            xy = !xy;
            ud = !ud;
        }
        if (xy) {
            if (ud) {
                y++;
            } else {
                y--;
            }
        } else {
            if (ud) {
                x++;
            } else {
                x--;
            }
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cout << setw(4) << a[x][y];
        }
        cout << endl;
    }
}

int min(int a, int b) {
    return a > b ? b : a;
}

int min4(int a, int b, int c, int d) {
    return min(min(a, b), min(c, d));
}

double sqr(double a) {
    return a * a;
}
bool IsPointInCircle(double x, double y, double xc, double yc, double r) {
    return (sqr(x-xc) + sqr(y-yc) <= sqr(r));
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
bool IsPointInSquare(double x, double y) {
    //return (x <= 1 && x >= -1 && y >= -1 && y <= 1);
    return ((1 - abs(x) - abs(y)) >= 0);
}
double power(double a, int n) {
    if (n == 0) return 1.0;
    if (n == 1) return a;
    if (n > 0) return a * power(a, n - 1);
    if (n < 0) return (1 / a) * power(a, n + 1);
}
int mDiv(int n, int div) {
    if (n % div == 0) return div;
    if (div*div > n) return n;
    return mDiv(n, div + 1);
}
int MinDivisor(int n) {
    if (n == 2 || n == 3) return n;
    return mDiv(n, 2);
}
bool IsPrime(int n) {
    if (n == 2 || n == 3) return true;
    return mDiv(n, 2) == n;
}

double qpower(double a, int n) {
    if (n == 0) return 1.0;
    if (n == 1) return a;
    if (n % 2 == 0) {
        a *= a; 
        n = n / 2; 
    }
    if (n > 0) return a * qpower(a, n - 1);
    if (n < 0) return (1 / a) * qpower(a, n + 1);
}
int sum_rec() {
    int n;
    cin >> n;
    if (n == 0) return 0;
    return n + sum_rec();
}
int fib_rec(int n) {
    if (n < 3) return 1;
    return fib_rec(n - 1) + fib_rec(n - 2);
}
using namespace std;

class SequenceSum{
  int count;
  public:
  string sum;
  SequenceSum (int);
  string showSequence(){
  	return sum;
  }
};

SequenceSum::SequenceSum (int c) {
  count = c;
  if (c == 0) {
  	sum = "0=0";
    return;
  }
  if (c < 0) {
    sum = to_string(c) + "<0";
    return;
  }
  int s = 0;
  
  for (int i=0; i < c; ++i) {
    sum += to_string(i) + "+";
    s += i;
  }
  s += c;
  sum += to_string(c) + " = " + to_string(s);
}

void test1() {
    cout << IsPointInSquare(1.0, 0.1) << abs(-1) << abs(-1.0) << std::abs(1) << std::abs(-1.0);
    cout << endl << power(2.3, 2);
    cout << endl << power(0.1, -2);
    cout << endl << MinDivisor(9) <<MinDivisor(13*17) <<MinDivisor(3) <<MinDivisor(4);
    cout << endl << MinDivisor(5) <<MinDivisor(6) <<MinDivisor(7) <<MinDivisor(8);
    cout << endl << IsPrime(73*13);
    cout << endl << qpower(2.3, 2);
    cout << endl << qpower(0.1, -2);
    //cout << endl << sum_rec();
    cout << endl << fib_rec(7);
}

int main() {
    SequenceSum seqsum (6);
    seqsum.showSequence();
    return 0;
}
// algorithm std::swap
