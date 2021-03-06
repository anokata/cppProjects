#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
/* *** 
 * когда на мелкие функции разбиваю только ради удобства - вызываю раз - можно их инлайнить!
 *
 */
//0.0  Написать процедуру тестирующую все следующие функции, и выводящую отчёт.
//1.0  написать функцию sumArray принимающую массив целых чисел и вычисляющих сумму.
int sumArray(int *array, int *end) {
    int sum = 0;
    for (; array != end; ++array) {
        sum += *array;
    }
    return sum;
}
//1.1  написать функцию avgArray принимающую массив целых чисел и вычисляющих среднее арифметическое.
//1.2  написать функцию lenString вычисляющую длинну переданной строки.
unsigned cstyle_string_len(const char *str) {
    unsigned len = 0;
    for (; *str; ++str, ++len);
    return len;
}
//2.0  Написать функцию max2 возвращающую большее из двух чисел.
//2.1  Написать функцию max3 принимающую 3 числа и возвращающую максимальное.
//2.2  Написать функцию sortArray принимающую массив чисел и сортирующую его с помощью функции max2
//2.3  Написать функцию maxArray принимающую массив целых чисел и находящую максимальное значение.
//2.4  Написать функцию is_member проверяющая встречается ли строка в массиве строк.
//2.5  Написать функцию overlapping принимающую два массива и возвращую True если у массивов есть хотя бы один общий элемент. можно использовать is_member.
//3.0  написать функцию принимающую два массива целых чисел и возвращающую массив разности элементов. Result = X - Y
//3.1  написать функцию принимающую массив целых чисел и целое число, и вычисляющих сумму элементов меньших переданного числа.
//4.0  написать функцию isInRectangle принимающую 4 целых числа - декартовы координаты углов прямоугольника и два числа - координаты точки. функция должна определять находится ли точка внутри прямоугольника.
//4.1  написать функцию greaterThan принимающую массив целых чисел и число, возвращающую массив чисел превыщающих переданное. (смотри про динамические массивы)
//5.0  написать функцию isVowel проверяющая символ на гласный(True)\согласный(False)
//5.1  написать функцию is_palindrome проверяющая строку на палиндром, вида "радар"
//5.2  написать функцию reverseString переворачивающую строку. 'abcd' -> 'dcba'
//5.3  написать функцию stringToNumber для преобразования строки содержащую десятичное число в число integer. строка состоит из символов, подобна массиву из char. каждый char это код символа в кодировке. коды цифр - 48 = '0'  можно использовать функции ORD CHR, смотрим справку, ищем примеры. CHR(50) == '2', ORD('3')==51
//5.4  написать функцию numberToString преобразования числа в строку.
//5.5  Написать функцию strCmpGT принимающую две строки и возвращающую True если первая больше второй.(сравнивая в лексикографическом порядке) Например:  ab > aa    aba < ca    aba < z    abc < abca
//5.6  Напсать функцию sortStringArray сортирующую массив строк в лексикографическом порядке, пользуясь функцией strCmpGT.
//6.0  написать функцию fileStringChange для замены в файле заданной строку на другую заданную.
//6.1  написать функцию fileStringReverse для переворачивания файла построчно, с конца в начало и обращающую и каждую строку функцией reverseString.
//7.0  написать функцию вычисляющую факториал числа не используя циклы. 
//7.1  написать функцию суммирующую массив чисел не используя циклы.
//7.2  написать функцию перемножающую массив чисел не используя циклы.
//8.0  написать функцию принимающую матрицу(двумерный массив) символов и два символа и заполняющую первыми символами диагонали, а вторыми символами элементы с обоими чётными индексами.
//8.1  написать процедуру печатающую матрицу символов, поэлементно, без пробелов, каждую строку с новой строки.
//8.2 Напиши функцию которая преобразует массив слов в массив чисел представляющих длинну каждого слова.
//8.3 Напиши функцию find_longest_word которая принимает массив слов и возвращает длинну самого длинного.

//8.4 Напиши функцию filter_long_words которая принимает массив слов и целое число N, и возвращает массив слов длинны больше N.
typedef std::vector<std::string> WordVector;
WordVector filter_long_words(WordVector words, int n) {
    WordVector result;
    for (std::string s : words) {
        if (s.size() > n) {
            result.push_back(s);
        }
    }
    return result;
}

void test_filterlw_array(WordVector v, int n, int mustbe) {
    WordVector r;
    r = filter_long_words(v, n);
    std::cout << "result:\n";
    for (auto s : r) { 
        std::cout << "\t-> " << s << "\n";
    }
    assert(r.size() == mustbe);
}

void test_filterlw() {
    std::cout << "\033[0;36m" << "+++ Test Filter LW\n" << "\033[0;37m";

    WordVector v = {"abc", "de", "zxcvb"};
	test_filterlw_array(v, 3, 1);
    test_filterlw_array(WordVector{"abc"}, 3, 0);
	test_filterlw_array(WordVector{"a", "b", "cd", "de"}, 1, 2);

    std::cout << "--- End Test\n";
}
/* ***** 8.4. end *** */

void test_arrays() {
    int arr[] = {1,2,3};
    assert(sumArray(arr, arr + 3) == 6);
    int arr2[] = {3,2,3};
    assert(sumArray(arr2, arr2 + 3) == 8);
}

void test_string_len() {
    cout << "str len tst" << endl;
    const char *str1 = "some";
    const char *str2 = "";
    const char *str3 = "1";
    assert(cstyle_string_len(str1) == 4);
    assert(cstyle_string_len(str2) == 0);
    assert(cstyle_string_len(str3) == 1);
}

void test_all() {
    test_arrays();
    test_string_len();
    test_filterlw();
}

int main() {
    cout << "start\n";
    test_all();
    std::stringstream ss;
    ss << 123;
    ss << " x .x dD.";
    std::cout << ss.str() << std::endl;
    std::cout << std::showbase << std::hex << 123456 << std::endl;
    return 0;
}

// https://stackoverflow.com/a/236803
//stringstream
//std::getline
//std::back_inserter

