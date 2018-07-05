#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
const int SPREAD = 10;
const int INIT_LENGTH = 10;
typedef unsigned char ArrayVal;

int main() {
    vector<ArrayVal> data;
    std::srand(unsigned(std::time(0)));

    for (int i = 0; i < INIT_LENGTH; ++i) {
        int value = std::rand() % SPREAD + 48;
        data.push_back(value);
    }

    std::cout << "Init array: ";
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << *it;
    }
    
    ArrayVal nextvalue = std::rand() % SPREAD + 48;
    std::cout << "\nNext value must be " << nextvalue;

    return 0;
}
