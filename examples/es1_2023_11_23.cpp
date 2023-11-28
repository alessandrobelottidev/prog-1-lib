#include "../include/magic/magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * Scrivere un programma che, dato in input un file con un intero per
 * riga, crea una lista concatenata con i numeri contenuti nel file
 */
int main() {
    ifstream inputFile("../examples/input.txt");

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