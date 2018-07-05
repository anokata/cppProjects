#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
const int SPREAD = 10;
const int INIT_LENGTH = 10;
typedef unsigned char ArrayVal;
const ArrayVal ERROR_VAL = -1;

ArrayVal predict_next_value(vector<ArrayVal> init);

int main() {
    vector<ArrayVal> data;
    std::srand(unsigned(std::time(0)));

    for (int i = 0; i < INIT_LENGTH; ++i) {
        int value = std::rand() % SPREAD;
        data.push_back(value);
    }

    std::cout << "Init array: ";
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << (char)(*it + '0');
    }
    
    ArrayVal nextvalue = std::rand() % SPREAD;
    std::cout << "\nNext value must be " << (char)(nextvalue + '0');

    std::cout << "\nPredicted: " << (char)(predict_next_value(data) + '0');

    return 0;
}

ArrayVal eval_rpn(string program, vector<ArrayVal> data) {
    vector<ArrayVal> stack;
    ArrayVal result;
    cout << char(data[1] + '0'); 

    for (auto it = program.begin(); it != program.end(); ++it) {
        char instruction = *it;

        if (instruction >= '0' && instruction <= '9') {
            stack.push_back(data[(int)(instruction - '0')]);
            cout << "push " << (ArrayVal) (stack.back() + '0') << "\n";
        }

        switch (instruction) {
            case '+':
                if (stack.size() < 2) return ERROR_VAL;
                ArrayVal right_operand = stack.back();
                stack.pop_back();
                ArrayVal left_operand = stack.back();
                stack.pop_back();
                result = left_operand + right_operand;
                //cout << "X" << left_operand;
                break;
        }
    }

    return result;
}

ArrayVal predict_next_value(vector<ArrayVal> data) {
    /* Program in reverse polish notation RPN */
    /* Instructions: 
     * + - * / %
     * 1 2 3 ... indexes of values of init data array
     * */
    string program;
    // test
    program = "12+";


    return eval_rpn(program, data);
}

