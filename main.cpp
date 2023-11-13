#include <iostream>
#include "magic.hpp"

using namespace std;
using namespace magic;

// Example usage of registering and calling a function with arguments
void exampleFunction(const vector<string>& args) {
    if (args.size() >= 2) {
        cout << "Example Function called with arguments: " << args[0] << " and " << args[1] << endl;
    }
}

int main() {
    // Example usage of logAndCall
    vector<string> args = { "arg1", "arg2" };
    debug::logAndCall("Calling Function:", "exampleFunction", exampleFunction, args);


    // Example print matrix
    debug::log("Print myMatrix", debug::INFO);

    matrix::Matrix myMatrix(3,3);

    for (int i = 0; i < myMatrix.rows; ++i)
        for (int j = 0; j < myMatrix.cols; ++j)
            myMatrix.set(i,j, i*myMatrix.cols + j);

    myMatrix.print();


    // Example transpose matrix
    debug::log("Transpose myMatrix", debug::INFO);

    matrix::transpose(myMatrix);
    myMatrix.print();


    // Example of invalid inverse matrix
    debug::log("Inverse of invalid myMatrix", debug::INFO);

    try {
        matrix::Matrix newMatrix(myMatrix);
        inverse(newMatrix);

        debug::log("Inverse of myMatrix");
        newMatrix.print();

        debug::log("Checking that the inverse is correct");
        matrix::Matrix identity = dotProduct(myMatrix, newMatrix);

        debug::log("Identity matrix");
        identity.print();
    } catch (std::runtime_error& e) {
        debug::log(e.what(), debug::ERROR);
    }

    // Example of valid inverse matrix
    debug::log("Inverse of valid matrix", debug::INFO);
    try {
        matrix::Matrix m1(3,3, new int*[3]{
            new int[3]{1,0,0},
            new int[3]{0,1,0},
            new int[3]{0,0,1}
        });

        debug::log("Matrix m1");
        m1.print();
        debug::log("Determinant of m1 is " + to_string(determinant(m1)));

        matrix::Matrix m2(m1.rows, m1.cols);

        debug::log("Matrix m2 (inverse of m1)");
        m2 = inverse(m1);
        m2.print();

        debug::log("Checking that the inverse is correct");
        matrix::Matrix identity = dotProduct(m1, m2);

        debug::log("Identity matrix");
        identity.print();
    } catch (std::runtime_error& e) {
        debug::log(e.what(), debug::ERROR);
    }

    return 0;
}
