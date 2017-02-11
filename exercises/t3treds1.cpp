#include <iostream>
#include <vector>
#include <array>
using namespace std;

void containers() {
    vector <int> v1(10); // динамический массив в куче.
    cout << v1.capacity();
    v1.resize(32);
    cout << v1.capacity();
    v1.reserve(132);
    cout << v1.capacity();
    v1.resize(3);
    //v1.insert( .erase .pop_back
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(5);
    for (vector <int>::iterator i = v1.begin(); i != v1.end(); i++) {
        cout << *i << ' ';
    }
    for (vector <int>::const_iterator i = v1.cbegin(); i != v1.cend(); i++) {}
        cout << endl;
    for (auto i = v1.rbegin(); i != v1.rend(); i++) { // Reverse
        cout << *i << ' ';
    }
    // массивы: vector, arrya
    array <int, 20> a1; // не динамический. на стеке(если объявлен на стеке)
    list<int> l1; // двусвязный список push_front pop_front push_back insert erase(from to) remove(val)
    forward_list<int> fl1;// односвязный список.
    deque<int> dq; // куски массива связанные в список
    set<int> s1; // ассоциативный упорядоченный, Дерево бинарное поиска балансированное(красно черное). TODO make on C
    multiset<int> ms1; // c повторяющимися
    map<int, int> m1;
    //multi_map
    //unordered_set<string> // реализован хеш-таблицей
    //кольцевой буфер
    //boost::circular_buffer
    return 0;
}

int main() {
}
