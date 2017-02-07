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

int main() {
    auto d = input_string_dict();
    string s;
    cin >> s;
    cout << d[s];
    return 0;
}
