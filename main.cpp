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
    matrix::Matrix myMatrix(3,3);

    for (int i = 0; i < myMatrix.rows; ++i)
        for (int j = 0; j < myMatrix.cols; ++j)
            myMatrix.set(i,j, i*myMatrix.cols + j);

    debug::log("Print matrix");
    myMatrix.print();


    // Example transpose matrix
    matrix::transpose(myMatrix);
    debug::log("Print matrix");
    myMatrix.print();

    return 0;
}
