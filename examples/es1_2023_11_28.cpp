#include "magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * scrivere un programma che prenda in ingresso un file con un intero per
 * riga e lo copi su un altro file con le righe in ordine inverso usando uno stack a lista concatenata
 */

int main() {
    ifstream inputFile("../examples/input3.txt");

    if (!inputFile.is_open()) {
        debug::log("Could not open input file", debug::ERROR);
        return -1;
    }

    istream& is = inputFile;

    ds::struct_stack<int> stack;

    ds::init(stack);

    while(!is.eof()) {
        string line;
        getline(is, line);

        try {
            int value = stoi(line);
            ds::push(value, stack);
        } catch (invalid_argument) {
            debug::log("Couldnt read an integer on this line", debug::ERROR);
            exit(-1);
        }
    }

    // Create an output file called 'output.txt' and write the stack to it
    ofstream outputFile("../examples/output.txt");

    if (!outputFile.is_open()) {
        debug::log("Could not open output file", debug::ERROR);
        return -1;
    }

    while (!ds::emptyp(stack)) {
        int value;
        ds::top(value, stack);
        outputFile << value << endl;
        ds::pop(stack);
    }

    outputFile.close();

    ds::deinit(stack);

    return 0;
}