TEST_CASE("Data structures", "[datastructures]") {
    SECTION("Stack") {
        SECTION("Linked List Stack") {
            ds::ll_stack<int> stack;

            ds::init(stack);

            CHECK(ds::size(stack) == 0);

            CHECK(ds::push(1, stack) == 1);
            CHECK(ds::push(2, stack) == 1);
            CHECK(ds::push(3, stack) == 1);
            CHECK(ds::push(4, stack) == 1);
            CHECK(ds::push(5, stack) == 1);

            CHECK(ds::size(stack) == 5);

            int topElement;
            CHECK(ds::top(topElement, stack) == 1);
            CHECK(topElement == 5);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);

            CHECK(ds::size(stack) == 2);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);

            CHECK(ds::size(stack) == 0);

            ds::deinit(stack);
        }

        SECTION("Dynamic Array Stack") {
            ds::dynamic_array_stack<int> stack;

            CHECK(ds::push(1, stack) == 1);
            CHECK(ds::push(2, stack) == 1);
            CHECK(ds::push(3, stack) == 1);
            CHECK(ds::push(4, stack) == 1);
            CHECK(ds::push(5, stack) == 0);

            int topElement;
            CHECK(ds::top(topElement, stack) == 1);
            CHECK(topElement == 4);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);

            CHECK(ds::top(topElement, stack) == 1);
            CHECK(topElement == 1);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 0);
        }

        SECTION("Static Array Stack") {
            ds::static_array_stack<int> stack;

            CHECK(ds::push(1, stack) == 1);
            CHECK(ds::push(2, stack) == 1);
            CHECK(ds::push(3, stack) == 1);
            CHECK(ds::push(4, stack) == 1);
            CHECK(ds::push(5, stack) == 0);

            int topElement;
            CHECK(ds::top(topElement, stack) == 1);
            CHECK(topElement == 4);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 1);

            CHECK(ds::top(topElement, stack) == 1);
            CHECK(topElement == 1);

            CHECK(ds::pop(stack) == 1);
            CHECK(ds::pop(stack) == 0);
        }
    }

    SECTION("Queue") {
        SECTION("Linked List Queue") {
            ds::ll_queue<int> queue;

            ds::init(queue);

            CHECK(ds::size(queue) == 0);

            CHECK(ds::enqueue(1, queue) == 1);
            CHECK(ds::enqueue(2, queue) == 1);
            CHECK(ds::enqueue(3, queue) == 1);
            CHECK(ds::enqueue(4, queue) == 1);
            CHECK(ds::enqueue(5, queue) == 1);

            CHECK(ds::size(queue) == 5);

            int frontElement;
            CHECK(ds::front(frontElement, queue) == 1);
            CHECK(frontElement == 1);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);

            CHECK(ds::size(queue) == 2);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);

            CHECK(ds::size(queue) == 0);

            ds::deinit(queue);
        }

        SECTION("Dynamic Array Queue") {
            ds::dynamic_array_queue<int> queue;

            CHECK(ds::enqueue(1, queue) == 1);
            CHECK(ds::enqueue(2, queue) == 1);
            CHECK(ds::enqueue(3, queue) == 1);
            CHECK(ds::enqueue(4, queue) == 1);
            CHECK(ds::enqueue(5, queue) == 1);

            int frontElement;
            CHECK(ds::front(frontElement, queue) == 1);
            CHECK(frontElement == 1);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);

            CHECK(ds::front(frontElement, queue) == 1);
            CHECK(frontElement == 4);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);
        }

        SECTION("Static Array Queue") {
            ds::static_array_queue<int> queue;

            CHECK(ds::enqueue(1, queue) == 1);
            CHECK(ds::enqueue(2, queue) == 1);
            CHECK(ds::enqueue(3, queue) == 1);
            CHECK(ds::enqueue(4, queue) == 1);
            CHECK(ds::enqueue(5, queue) == 0);

            int frontElement;
            CHECK(ds::front(frontElement, queue) == 1);
            CHECK(frontElement == 1);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 1);

            CHECK(ds::front(frontElement, queue) == 1);
            CHECK(frontElement == 4);

            CHECK(ds::dequeue(queue) == 1);
            CHECK(ds::dequeue(queue) == 0);

            CHECK(ds::front(frontElement, queue) == 0);

            CHECK(ds::dequeue(queue) == 0);
        }
    }

    SECTION("Linked List") {
        SECTION("Singly Linked List") {
            ds::singly_linked_list<int> list;

            CHECK(ds::push_front(1, list) == 1);
            CHECK(ds::push_front(2, list) == 1);
            CHECK(ds::push_front(3, list) == 1);
            CHECK(ds::push_front(4, list) == 1);
            CHECK(ds::push_front(5, list) == 1);

            CHECK(ds::size(list) == 5);

            int frontElement;
            CHECK(ds::front(frontElement, list) == 1);
            CHECK(frontElement == 5);

            CHECK(ds::pop_front(list) == 1);
            CHECK(ds::pop_front(list) == 1);
            CHECK(ds::pop_front(list) == 1);

            CHECK(ds::size(list) == 2);

            CHECK(ds::pop_front(list) == 1);
            CHECK(ds::pop_front(list) == 1);

            CHECK(ds::size(list) == 0);
        }
    }

    SECTION("Tree") {
        SECTION("Binary Search Tree") {

        }
    }
}
