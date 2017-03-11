#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <locale>
#include <map>

using namespace std;

class Machine {
    unsigned int ip; // Instruction pointer
    unsigned int dp; // Data pointer
    string code;
    string input;
    vector<unsigned char> data;
    string out;
    //vector<int> stack;
    map<int, int> loops;
    public:
    Machine(string code, string input) 
      : code(code), input(input) {
        ip = 0;
        dp = 0;
        for (int i = 0; i < 16; i++) 
            data.push_back(0);
        code_loops_analyse();
    }
    void step();
    string getOutput();
    void printState();
    void inst_dt_inc(); // >
    void inst_dt_dec(); // <
    void inst_data_inc(); // +
    void inst_data_dec(); // -
    void inst_out(); // .
    void inst_in(); // ,
    void inst_loop_start(); // [
    void inst_loop_end(); // ]
    void run();

    private:
    void code_loops_analyse();
};

void Machine::code_loops_analyse() {
    vector<int> stack;
    for (int p = 0; p < code.size(); p++) {
        if (code[p] == '[') {
            stack.push_back(p);
        }
        if (code[p] == ']') {
            if (stack.size() == 0) {
                cout << "ERROR too much ']'!\n";
                exit(1);
            }
            loops[stack.back()] = p;
            loops[p] = stack.back();
            stack.pop_back();
        }
    }
}

void Machine::inst_loop_start() {
    if (data[dp] == 0) {
        ip = loops[ip];
    }
}

void Machine::inst_loop_end() {
    if (data[dp] != 0) {
        ip = loops[ip];
    }
}

void Machine::inst_in() {
    if (input.size() != 0 ) {
        data[dp] = input[0];
        input = input.substr(1);
    } else {
        data[dp] = 0;
    }
}

void Machine::inst_out() {
    out += data[dp];
}

void Machine::inst_data_inc() {
    data[dp]++;
}

void Machine::inst_data_dec() {
    data[dp]--;
}

void Machine::inst_dt_inc() {
    dp++;
    if (dp > data.size()) {
        //dp = 0;
        data.push_back(0);
    }
}

void Machine::inst_dt_dec() {
    dp--;
    if (dp < 0) dp = data.size() - 1;
}

void Machine::printState() {
    cout << "IP: " << ip << "  " << "DP: " << dp << endl;
    for (int base = 0; base < data.size(); base += 16) {
        if (base + 16 > data.size()) break;
        cout << "0x";
        cout << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << base << ' ';
        for (int i = 0; i < 16; i++) {
            cout << std::hex << std::uppercase << std::setfill('0');
            cout << std::setw(2) << (unsigned int)data[base + i] << ' ';
        }
        cout << "    ";
        for (int i = 0; i < 16 && i+base < data.size(); i++) {
            if (isprint(data[base+i])) {
                cout << data[base + i];
                }
        }
        cout << endl;
        //cout << std::resetiosflags;
        cout << "loops: ";
        for (auto it : loops) {
            cout << it.first << ':' << it.second << ' ';
        }
        cout << ".";
        cout << endl;
        cout << code << endl;
        for (int i = 0; i < ip; ++i) cout << ' ';
        cout << '^' << endl;
        cout << std::dec;
        cout << "out:[" << out << "]" << "BIN{" << (unsigned int) out[0] << "}" << out.size() << endl;
    }
}

string Machine::getOutput() {
    return out;
}

void Machine::step() {
    switch (code[ip]) {
        case '>':
            inst_dt_inc();
            break;
        case '<':
            inst_dt_dec();
            break;
        case '-':
            inst_data_dec();
            break;
        case '+':
            inst_data_inc();
            break;
        case '.':
            inst_out();
            break;
        case ',':
            inst_in();
            break;
        case '[':
            inst_loop_start();
            break;
        case ']':
            inst_loop_end();
            break;
    }
    ip++;
}

void Machine::run() {
    while(ip < code.size()) {
        step();
        //usleep(200000);
        //printState();
    }
}

std::string brainLuck(std::string code, std::string input)
{
    Machine m(code, input);
    m.run();
    //m.printState();
    return m.getOutput();
}

int main() {
    string in = "Hi";
    in.append(1,(char)255);
    cout << brainLuck(",+[-.,+]", in);

    std::string mw = "codewars";
    mw.append(1,(char)0);
    cout << brainLuck(",[.[-],]",mw);

    std::string dw;
    dw.append(1, (char) 7);
    dw.append(1, (char) 3);
    std::string result;
    cout << brainLuck(",>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.",dw);
      
    return 0;
}
