#include "../include/magic/magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * Aggiungere una terza funzione al programma:
 * void stampaListaInvertita(lista listaDiNumeri);
 * che stampa la lista in maniera invertita.
 */

void printInReverseRecursively(ds::node<string>* node) {
    if (node == nullptr) {
        return;
    }

    printInReverseRecursively(node->next);

    cout << node->val << endl;
}

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

    printInReverseRecursively(list.head);

    return 0;
}