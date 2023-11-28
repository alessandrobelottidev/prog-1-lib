#include "magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * Scrivere un programma che, data una parola in input (massimo 100
 * caratteri), dica se è palindroma oppure no usando una pila e/o una coda.
 * Nota: non potete sfruttare la conoscenza della lunghezza della parola
 * (non potete nemmeno calcolarla)
 */

int main() {
    std::string word = io::read<std::string>(std::cin,
                                             "Inserisci una parola e ti diro se e' palindroma: ",
                                             "La parola deve essere di massimo 100 caratteri",
                                             [](std::string s) { return s.length() <= 100; });

    ds::struct_stack<char> stack;
    ds::struct_queue<char> queue;

    ds::init(stack);
    ds::init(queue);

    for (int i = 0; i < word.length(); ++i) {
        char c = word[i];

        ds::push(c, stack);
        ds::enqueue(c, queue);
    }

    bool isPalindrome = true;
    bool next = true;

    while ((!ds::emptyp(stack) && !ds::emptyp(queue)) && next) {
        char c1, c2;
        ds::top(c1, stack);
        ds::pop(stack);
        ds::front(c2, queue);
        ds::dequeue(queue);

        if (c1 != c2) {
            isPalindrome = false;
            next = false;
        }
    }

    if (isPalindrome) {
        cout << "La parola e' palindroma" << endl;
    } else {
        cout << "La parola non e' palindroma" << endl;
    }

    return 0;
}