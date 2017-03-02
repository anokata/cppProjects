#include <iostream>
using namespace std;

class Person {
    protected:
    char name[100];
    int age;
    public:
    virtual void getdata() {};
    virtual void putdata() {};
};
class Professor : public Person{
    int publications;
    static int id_gen;
    int cur_id;
    public:
    Professor() {
        cur_id = id_gen++;
    }
    void getdata() {
        cin >> name >> age >> publications;
    }
    void putdata() {
        cout << name  << ' ' << age << ' ' << publications << ' ' << cur_id << endl;
    }
    
};
int Professor::id_gen = 1;

class Student : public Person {
   int cur_id;
   static int id_gen;
   int marks[6];
   public:
   Student() {
       cur_id = id_gen++;
   }
   void getdata() {
        cin >> name >> age;
        for (int i=0; i<6; i++) {
            cin >> marks[i];
        }
    }
    void putdata() {
        cout << name  << ' ' << age << ' ';
        int sum = 0;
        for (int i=0; i<6; i++) {
            sum += marks[i];
        }
        cout << sum << ' ' << cur_id << endl;
    }
};
int Student::id_gen= 1;

int main() {
    Professor p;
    Professor p2;
    Student s;
    p.putdata();
    p2.putdata();

    return 0;
}
