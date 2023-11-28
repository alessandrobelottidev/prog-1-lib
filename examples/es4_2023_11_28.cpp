#include "magic.hpp"
#include <fstream>

using namespace std;
using namespace magic;

/*
 * Scrivere un programma che inverta gli elementi di una pila usando una coda.
 */

int main() {
    ds::struct_stack<int> stack;

    ds::init(stack);

    for (int i = 0; i < 10; ++i) {
        ds::push(i, stack);
    }

    ds::print(stack);

    ds::struct_queue<int> queue;

    ds::init(queue);

    while (!ds::emptyp(stack)) {
        int el;
        ds::top(el, stack);
        ds::pop(stack);
        ds::enqueue(el, queue);
    }

    while (!ds::emptyp(queue)) {
        int el;
        ds::front(el, queue);
        ds::dequeue(queue);
        ds::push(el, stack);
    }

    ds::print(stack);

    ds::deinit(stack);

    ds::deinit(queue);

    return 0;
}