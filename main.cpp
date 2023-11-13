#include <iostream>
#include "magic.hpp"

using namespace std;
using namespace magic;

void exampleFunction(const vector<string>& args) {
    if (args.size() >= 2)
        cout << "Example Function called with arguments: " << args[0] << " and " << args[1] << endl;
}

int main() {
    // Example usage of logAndCall
    // vector<string> args = { "arg1", "arg2" };
    // debug::logAndCall("Calling Function:", "exampleFunction", exampleFunction, args);


    // Example print matrix
    debug::logBlock("PRINT, TRANSPOSE", []{
        debug::log("Print matrix", debug::DEBUG);
        matrix::Matrix<float> myMatrix(3,3);

        for (int i = 0; i < myMatrix.rows; ++i)
            for (int j = 0; j < myMatrix.cols; ++j)
                myMatrix.set(i,j, i * myMatrix.cols + j);

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

    return 0;
}
