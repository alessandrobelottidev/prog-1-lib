#include "magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * scrivere un programma che legge una sequenza di caratteri in input
 * dall’utente e determina se le parentesi sono “bilanciate” o meno. Usando uno stack
 */

int main() {
    std::string sequence = io::read<std::string>(std::cin, "Inserisci una sequenza di parentesti e ti diro se sono bilanciate: ");

    ds::ll_stack<char> stack;

    ds::init(stack);

    for (int i = 0; i < sequence.length(); ++i) {
        char c = sequence[i];

        if (c == '(') {
            ds::push(c, stack);
        } else if (c == ')') {
            if (ds::emptyp(stack)) {
                cout << "Le parentesi non sono bilanciate" << endl;
                return 0;
            }
            ds::pop(stack);
        }
    }

    if (ds::emptyp(stack)) {
        cout << "Le parentesi sono bilanciate" << endl;
    } else {
        cout << "Le parentesi non sono bilanciate" << endl;
    }

    ds::deinit(stack);

    return 0;
}