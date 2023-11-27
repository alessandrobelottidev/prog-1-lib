#include <iostream>
#include <fstream>
#include "../include/magic/magic.hpp"
#define TESTING 1


using namespace std;
using namespace magic;

#define AUTOMATED_TESTING 1


void exampleFunction(const vector<string>& args) {
    debug::log("This is an example function", debug::DEBUG);
    debug::log("Arguments: ", debug::DEBUG);
    for (const string& arg : args)
        debug::log(arg, debug::DEBUG);
}


int main() {
    debug::logBlock("Example of logBlock", []{
        debug::log("This is a log message inside a logBlock", debug::DEBUG);
    });


    debug::logBlock("Example usage of logAndCall", [] {
        debug::logAndCall("Calling Function:", "exampleFunction", exampleFunction, vector<string>{ "arg1", "arg2" });
    });


    debug::logBlock("String operations", []{
        debug::log("To upper case: " + strOp::toUpperCase("Hello World!"), debug::DEBUG);
        debug::log("To lower case: " + strOp::toLowerCase("Hello World!"), debug::DEBUG);
        debug::log("Trim: " + strOp::trim("   Hello World!   "), debug::DEBUG);
        debug::log("Trim left: " + strOp::trimLeft("   Hello World!   "), debug::DEBUG);
        debug::log("Trim right: " + strOp::trimRight("   Hello World!   "), debug::DEBUG);
        debug::log("Split: " + strOp::join(strOp::split("Hello World!", " "), ", "), debug::DEBUG);
        debug::log("Substring: " + strOp::substring("Hello World!", 6, 11), debug::DEBUG);
        debug::log("Replace: " + strOp::replaceOnce("Hello World World!", "World", "Universe"), debug::DEBUG);
        debug::log("Replace all: " + strOp::replaceAll("Hello World World!", "World", "Universe"), debug::DEBUG);
        debug::log("Replace all in between 6 and 11: " + strOp::replaceAllInBetween("Hello World World!","World", "Universe", 6, 11), debug::DEBUG);
        debug::log("Equals ignore case: " + to_string(strOp::equalsIgnoreCase("Hello World!", "hello world!")), debug::DEBUG);
        debug::log("Starts with: " + to_string(strOp::startsWith("Hello World!", "Hello")), debug::DEBUG);
        debug::log("Ends with: " + to_string(strOp::endsWith("Hello World!", "World!")), debug::DEBUG);
        debug::log("Contains: " + to_string(strOp::contains("Hello World!", "World")), debug::DEBUG);
        debug::log("Repeat: " + strOp::repeat("Hello World! ", 3), debug::DEBUG);
        debug::log("Pad left: " + strOp::padLeft("Hello World!", 20, '*'), debug::DEBUG);
        debug::log("Pad right: " + strOp::padRight("Hello World!", 20, '*'), debug::DEBUG);
        debug::log("Pad center: " + strOp::padCenter("Hello World!", 20, '*'), debug::DEBUG);
        debug::log("Count occurrences: " + to_string(strOp::countOccurrences("Hello World!", 'o')), debug::DEBUG);
        debug::log("Remove all occurrences: " + strOp::removeAllOccurrences("Hello World!", 'o'), debug::DEBUG);
    });


    debug::logBlock("Io operations", [] {
        std::ifstream inputFile("../tests/io_ops_tests_input.txt");

        if (AUTOMATED_TESTING && !inputFile.is_open()) {
            debug::log("Could not open test file, run manually", debug::ERROR);
            return;
        }

        istream& is = AUTOMATED_TESTING ? inputFile : std::cin;

        struct Student {
            int id;
            string name;
            float gpa;
        };

        debug::log("Read  a single student", debug::DEBUG);

        Student student = {
                io::read<int>(is, "Enter student id: "),
                io::read<string>(is, "Enter student name: "),
                io::read<float>(is, "Enter student gpa: ", "Invalid GPA", [](const float& gpa) {
                    return gpa >= 0 && gpa <= 4;
                })
        };

        debug::log("Student id: " + to_string(student.id), debug::DEBUG);
        debug::log("Student name: " + student.name, debug::DEBUG);
        debug::log("Student gpa: " + to_string(student.gpa), debug::DEBUG);

        debug::log("Read a menu option", debug::DEBUG);

        int option = io::showMenu("Menu", "Select an option: ", {
                "Option 1",
                "Option 2",
                "Option 3"
        }, is);

        debug::log("Option selected: " + to_string(option), debug::DEBUG);
    });


    debug::logBlock("Matrix operations", []{
        debug::logBlock("PRINT, TRANSPOSE", []{
            debug::log("Print matrix", debug::DEBUG);
            matrix::Matrix<float> myMatrix(3,3);

            for (int i = 0; i < myMatrix.rows; ++i)
                for (int j = 0; j < myMatrix.cols; ++j)
                    myMatrix.set(i,j, (float) (i * myMatrix.cols + j));

            myMatrix.print();

            debug::log("Transpose matrix", debug::DEBUG);
            matrix::transpose(myMatrix);
            myMatrix.print();
        });


        debug::logBlock("Inverse of invalid matrix", []{
            matrix::Matrix<float> myMatrix(3,3);

            try {
                debug::log("Matrix myMatrix");
                myMatrix.print();
                debug::log("Determinant of myMatrix is " + to_string(determinant(myMatrix)));

                debug::log("Matrix newMatrix (inverse of myMatrix)");
                matrix::Matrix<float> newMatrix = inverse(myMatrix);
                newMatrix.print();

                debug::log("Checking that the inverse is correct");
                matrix::Matrix<float> identity = dotProduct(myMatrix, newMatrix);

                debug::log("Identity matrix");
                identity.print();
            } catch (std::runtime_error& e) {
                debug::log(e.what(), debug::ERROR);
            }
        });


        debug::logBlock("Inverse of valid matrix", [] {
            try {
                matrix::Matrix<float> m1(3,3, new float*[3]{
                        new float[3]{1,0,0},
                        new float[3]{0,1,0},
                        new float[3]{0,0,1}
                });

                debug::log("Matrix m1");
                m1.print();
                debug::log("Determinant of m1 is " + to_string(determinant(m1)));

                matrix::Matrix<float> m2(m1.rows, m1.cols);

                debug::log("Matrix m2 (inverse of m1)");
                m2 = inverse(m1);
                m2.print();

                debug::log("Checking that the inverse is correct");
                matrix::Matrix<float> identity = dotProduct(m1, m2);

                debug::log("Identity matrix");
                identity.print();
            } catch (std::runtime_error& e) {
                debug::log(e.what(), debug::ERROR);
            }
        });


        debug::logBlock("Usage of matrix of chars", [] {
            matrix::Matrix<char> crossword(5, 5);

            const char word[] = "HELLO";
            for (int i = 0; i < sizeof(word) - 1; ++i)
                crossword.set(4, i, word[i]);

            for (int i = 0; i < sizeof(word) - 1; ++i)
                crossword.set(i, 0, word[sizeof(word) - i - 2]);

            crossword.print();
        });
    });


    debug::logBlock("Data structures", []{
        debug::logBlock("STRUCT STACK", []{
            ds::struct_stack<int> stack;

            ds::init(stack);

            debug::log("Pushing 1, 2, 3, 4, 5 to stack", debug::DEBUG);
            debug::log("Pushed: " + to_string(push(1, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(2, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(3, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(4, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(5, stack)), debug::DEBUG);

            debug::log("Stack size: " + to_string(size(stack)), debug::DEBUG);

            int topElement;
            debug::log("Top element: " + to_string(top(topElement, stack)), debug::DEBUG);

            // Print stack
            debug::log("Stack: ", debug::DEBUG);
            print(stack);
            printBeautified(stack);

            debug::log("Popping 5 elements from stack", debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);

            debug::log("Stack size: " + to_string(size(stack)), debug::DEBUG);

            ds::deinit(stack);
        });

        debug::logBlock("DYNAMIC ARRAY STACK", []{
            ds::dynamic_array_stack<int> stack;

            debug::log("Pushing 1, 2, 3, 4, 5 to stack", debug::DEBUG);
            debug::log("Pushed: " + to_string(push(1, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(2, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(3, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(4, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(5, stack)), debug::DEBUG);

            int topElement;
            debug::log("Top element: " + to_string(top(topElement, stack)), debug::DEBUG);

            // Print stack
            debug::log("Stack: ", debug::DEBUG);
            print(stack);

            debug::log("Popping 5 elements from stack", debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);

            // Print stack
            debug::log("Stack: ", debug::DEBUG);
            print(stack);
        });

        debug::logBlock("STATIC ARRAY STACK", []{
            ds::static_array_stack<int> stack;

            debug::log("Pushing 1, 2, 3, 4, 5 to stack", debug::DEBUG);
            debug::log("Pushed: " + to_string(push(1, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(2, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(3, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(4, stack)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push(5, stack)), debug::DEBUG);

            int topElement;
            debug::log("Top element: " + to_string(top(topElement, stack)), debug::DEBUG);

            // Print stack
            debug::log("Stack: ", debug::DEBUG);
            print(stack);

            debug::log("Popping 5 elements from stack", debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop(stack)), debug::DEBUG);

            // Print stack
            debug::log("Stack: ", debug::DEBUG);
            print(stack);
        });

        debug::logBlock("STRUCT QUEUE", []{
            ds::struct_queue<int> queue;

            ds::init(queue);

            debug::log("Enqueueing 1, 2, 3, 4, 5 to queue", debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(1, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(2, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(3, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(4, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(5, queue)), debug::DEBUG);

            debug::log("Queue size: " + to_string(size(queue)), debug::DEBUG);

            int frontElement;
            debug::log("Front element: " + to_string(front(frontElement, queue)), debug::DEBUG);

            // Print queue
            debug::log("Queue: ", debug::DEBUG);
            print(queue);
            printBeautified(queue);

            debug::log("Dequeueing 5 elements from queue", debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);

            debug::log("Queue size: " + to_string(size(queue)), debug::DEBUG);

            ds::deinit(queue);
        });

        debug::logBlock("DYNAMIC ARRAY QUEUE", []{
            ds::dynamic_array_queue<int> queue;

            debug::log("Enqueueing 1, 2, 3, 4, 5 to queue", debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(1, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(2, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(3, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(4, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(5, queue)), debug::DEBUG);

            int frontElement;
            debug::log("Front element: " + to_string(front(frontElement, queue)), debug::DEBUG);

            // Print queue
            debug::log("Queue: ", debug::DEBUG);
            print(queue);

            debug::log("Dequeueing 5 elements from queue", debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);

            // Print queue
            debug::log("Queue: ", debug::DEBUG);
            print(queue);

            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
        });

        debug::logBlock("STATIC ARRAY QUEUE", []{
            ds::static_array_queue<int> queue;

            debug::log("Enqueueing 1, 2, 3, 4, 5 to queue", debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(1, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(2, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(3, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(4, queue)), debug::DEBUG);
            debug::log("Enqueued: " + to_string(enqueue(5, queue)), debug::DEBUG);

            int frontElement;
            debug::log("Front element: " + to_string(front(frontElement, queue)), debug::DEBUG);

            // Print queue
            debug::log("Queue: ", debug::DEBUG);
            print(queue);

            debug::log("Dequeueing 5 elements from queue", debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);

            // Print queue
            debug::log("Queue: ", debug::DEBUG);
            print(queue);

            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
            debug::log("Dequeued: " + to_string(dequeue(queue)), debug::DEBUG);
        });

        debug::logBlock("SINGLY LINKED LIST", []{
            // use all the functions from singly_linked_list.ipp
            ds::singly_linked_list<int> list;

            debug::log("Pushing 1, 2, 3 to front of list", debug::DEBUG);
            debug::log("Pushed to front: " + to_string(push_front(1, list)), debug::DEBUG);
            debug::log("Pushed to front: " + to_string(push_front(2, list)), debug::DEBUG);
            debug::log("Pushed to front: " + to_string(push_front(3, list)), debug::DEBUG);

            debug::log("List size: " + to_string(size(list)), debug::DEBUG);

            int frontElement;
            debug::log("Front element: " + to_string(front(frontElement, list)), debug::DEBUG);

            debug::log("List: ", debug::DEBUG);
            print(list);

            debug::log("Pushing 1, 2, 3 to list", debug::DEBUG);
            debug::log("Pushed: " + to_string(push_back(1, list)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push_back(2, list)), debug::DEBUG);
            debug::log("Pushed: " + to_string(push_back(3, list)), debug::DEBUG);

            debug::log("List size: " + to_string(size(list)), debug::DEBUG);

            int backElement;
            debug::log("Back element: " + to_string(back(backElement, list)), debug::DEBUG);

            debug::log("List: ", debug::DEBUG);
            print(list);

            debug::log("Popping 3 elements from list", debug::DEBUG);
            debug::log("Popped: " + to_string(pop_front(list)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop_front(list)), debug::DEBUG);
            debug::log("Popped: " + to_string(pop_front(list)), debug::DEBUG);

            debug::log("List size: " + to_string(size(list)), debug::DEBUG);

            debug::log("List: ", debug::DEBUG);
            print(list);
        });
    });


    debug::logBlock("Algorithms", []{
        debug::logBlock("Bubblesort", []{
            debug::log("Default sorting an array of integers", debug::DEBUG);
            int arr[] = { 5, 4, 3, 2, 1 };
            int n = sizeof(arr) / sizeof(arr[0]);

            io::writeArray("Array before sorting: ", arr, n);
            algo::bubbleSort(arr, n);
            io::writeArray("Array after sorting: ", arr, n);


            debug::log("Sorting an array of integers with custom comparison", debug::DEBUG);
            int arr2[] = { 23, 65, 12, 3, 9, 1, 0, 5, 7, 8, 2, 4, 6, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20 };
            n = sizeof(arr2) / sizeof(arr2[0]);

            io::writeArray("Array before sorting: ", arr2, n);
            algo::bubbleSort(arr2, n, *[](const int& a, const int& b) {
                // Strange sort where even numbers are sorted in descending order and odd numbers are sorted in ascending order
                if (a % 2 == 0 && b % 2 == 0)
                    return a > b;
                else if (a % 2 == 1 && b % 2 == 1)
                    return a < b;
                else
                    return a < b;
            });
            io::writeArray("Array after sorting: ", arr2, n);

            debug::log("Sorting an array of strings based on their length", debug::DEBUG);
            string arr3[] = { "Hello", "World", "This", "Is", "A", "Test" };
            n = sizeof(arr3) / sizeof(arr3[0]);

            io::writeArray("Array before sorting: ", arr3, n);
            algo::bubbleSort(arr3, n, *[](const string& a, const string& b) {
                return a.length() > b.length();
            });
            io::writeArray("Array after sorting: ", arr3, n);


            debug::log("Sorting a singly linked list of strings based on alphabetical order and then on length", debug::DEBUG);
            ds::singly_linked_list<string> list;

            for (int i = 0; i < n; ++i)
                push_back(arr3[i], list);

            debug::log("List before sorting: ", debug::DEBUG);
            print(list);

            algo::bubbleSort(list.head, list.tail, *[](const ds::node<string>& a, const ds::node<string>& b) {
                if (a.val < b.val)
                    return true;
                else if (a.val > b.val)
                    return false;
                else
                    return a.val.length() > b.val.length();
            });

            debug::log("List after sorting: ", debug::DEBUG);
            print(list);

            // Sort a list of integeres in ascending order but only up to a certain node (let's say the third)

            ds::singly_linked_list<int> list2;

            for (int i = 0; i < 10; ++i)
                push_back(i, list2);

            debug::log("List before sorting: ", debug::DEBUG);
            print(list2);

            algo::bubbleSort(list2.head, list2.head->next->next->next, *[](const ds::node<int>& a, const ds::node<int>& b) {
                return a.val > b.val;
            });

            debug::log("List after sorting: ", debug::DEBUG);
            print(list2);
        });

        debug::logBlock("Selection sort", []{
            debug::log("Default sorting an array of integers", debug::DEBUG);
            int arr[] = { 5, 4, 3, 2, 1 };
            int n = sizeof(arr) / sizeof(arr[0]);

            io::writeArray("Array before sorting: ", arr, n);
            algo::selectionSort(arr, n);
            io::writeArray("Array after sorting: ", arr, n);


            debug::log("Sorting an array of integers with custom comparison", debug::DEBUG);
            int arr2[] = { 23, 65, 12, 3, 9, 1, 0, 5, 7, 8, 2, 4, 6, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20 };
            n = sizeof(arr2) / sizeof(arr2[0]);

            io::writeArray("Array before sorting: ", arr2, n);
            algo::selectionSort(arr2, n, *[](const int& a, const int& b) {
                // Strange sort where even numbers are sorted in descending order and odd numbers are sorted in ascending order
                if (a % 2 == 0 && b % 2 == 0)
                    return a > b;
                else if (a % 2 == 1 && b % 2 == 1)
                    return a < b;
                else
                    return a < b;
            });
            io::writeArray("Array after sorting: ", arr2, n);

            debug::log("Sorting an array of strings based on their length", debug::DEBUG);
            string arr3[] = { "Hello", "World", "This", "Is", "A", "Test" };
            n = sizeof(arr3) / sizeof(arr3[0]);

            io::writeArray("Array before sorting: ", arr3, n);
            algo::selectionSort(arr3, n, *[](const string& a, const string& b) {
                return a.length() > b.length();
            });
            io::writeArray("Array after sorting: ", arr3, n);


            debug::log("Sorting a singly linked list of strings based on alphabetical order and then on length", debug::DEBUG);
            ds::singly_linked_list<string> list;

            for (int i = 0; i < n; ++i)
                push_back(arr3[i], list);

            debug::log("List before sorting: ", debug::DEBUG);
            print(list);

            algo::selectionSort(list.head, list.tail, *[](const ds::node<string>& a, const ds::node<string>& b) {
                if (a.val < b.val)
                    return true;
                else if (a.val > b.val)
                    return false;
                else
                    return a.val.length() > b.val.length();
            });

            debug::log("List after sorting: ", debug::DEBUG);
            print(list);

            // Sort a list of integeres in ascending order but only up to a certain node (let's say the third)
            ds::singly_linked_list<int> list2;

            for (int i = 0; i < 10; ++i)
                push_back(i, list2);

            debug::log("List before sorting: ", debug::DEBUG);
            print(list2);

            algo::selectionSort(list2.head, list2.head->next->next->next, *[](const ds::node<int>& a, const ds::node<int>& b) {
                return a.val > b.val;
            });

            debug::log("List after sorting: ", debug::DEBUG);
            print(list2);
        });
    });


    io::clearScreen();
}
