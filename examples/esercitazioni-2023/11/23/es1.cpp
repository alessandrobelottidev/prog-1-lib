#include "../../../../magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

int main() {
    ifstream inputFile("../examples/esercitazioni-2023/11/23/input.txt");

    if (!inputFile.is_open()) {
        debug::log("Could not open input file", debug::ERROR);
        return -1;
    }

    istream& is = inputFile;

    ds::singly_linked_list<string> list;

    while(!is.eof()) {
        string line;
        getline(is, line);

        ds::push_back(line, list);
    }

    ds::print(list);

    return 0;
}