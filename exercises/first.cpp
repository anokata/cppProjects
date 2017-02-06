#include <iostream>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cassert>
#include <algorithm> // sort

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
    show_array(a, 5);
    sort(a, a+5);
    show_array(a, 5);
}

int main() {
    return 0;
}
