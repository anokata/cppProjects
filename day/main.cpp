#include <iostream>
#include <fstream>
#include <string>
#include "csv.h"

int main(int argc, char *argv[]) {
    std::cout << "(l)\n";

    std::string filename = "sample.csv";
    char delimeter = ',';
    std::ifstream in;
    in.open(filename);
    std::string buf;

    /* Read headers */
    std::getline(in, buf, '\n');
    buf = "";

    while (buf.find("\n") == std::string::npos) {
        std::cout << buf;
        std::getline(in, buf, delimeter);
    }

    return 0;
}
