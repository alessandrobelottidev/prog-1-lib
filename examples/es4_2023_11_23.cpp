#include "../include/magic/magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

int main() {
    ifstream inputFile("../examples/input2.txt");

    if (!inputFile.is_open()) {
        debug::log("Could not open input file", debug::ERROR);
        return -1;
    }

    istream& is = inputFile;

    ds::singly_linked_list<int> list;

    int max = 0;
    while(!is.eof()) {
        string line;
        getline(is, line);

        int value = stoi(line);

        if (value > max)
            max = value;

        if (value >=0)
            ds::push_back(value, list);
    }

    ds::print(list);

    cout << "-----------" << endl;

    bool * sieveOfEratosthenes = math::sieveOfEratosthenes(max);

    ds::node<int> * current = list.head;
    ds::node<int> * previous = nullptr;
    while (current) {
        if (sieveOfEratosthenes[current->val]) {
            if (previous) {
                previous->next = current->next;
            } else {
                list.head = current->next;
            }
            delete current;
            current = previous ? previous->next : list.head;
        } else {
            previous = current;
            current = current->next;
        }
    }

    ds::print(list);

    return 0;
}