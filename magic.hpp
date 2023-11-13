#ifndef MAGIC_H
#define MAGIC_H

#include <string>
#include <functional>
#include <vector>

namespace magic {
    namespace debug {
        // ANSI escape codes for text colors
        const std::string ANSI_RESET = "\033[0m";
        const std::string ANSI_RED = "\033[31m";
        const std::string ANSI_GREEN = "\033[32m";
        const std::string ANSI_YELLOW = "\033[33m";
        const std::string ANSI_BLUE = "\033[34m";

        enum LogLevel { DEBUG, INFO, WARNING, ERROR };
        
        void log(const std::string& message, LogLevel level = DEBUG);
        void registerFunction(const std::string& functionName, 
                              std::function<void(const std::vector<std::string>&)> function);
        void callFunctionByName(const std::string& functionName, const std::vector<std::string>& arguments);
        void logAndCall(const std::string& title,
                        const std::string& functionName,
                        std::function<void(const std::vector<std::string>&)> function,
                        const std::vector<std::string>& arguments);
    }

    namespace matrix {
        struct Matrix {
            int rows;
            int cols;
            int **data;

            Matrix(int rows, int cols); // Default constructor
            Matrix(int rows, int cols, int **data); // Constructor with data
            Matrix(const Matrix &other); // Copy constructor for deep
            ~Matrix(); // Destructor to free memory

            Matrix& operator=(const Matrix &other); // Assignment operator for deep copy

            void set(int row, int col, int value) const;
            int get(int row, int col) const;

            bool isSquared() const;
            void print() const;
        };

        void transpose(Matrix& matrix);
        void sum(Matrix& matrix1, int value);
        void sum(Matrix& matrix1, Matrix& matrix2);
        void subtract(Matrix& matrix1, Matrix& matrix2);
        void scalarProduct(Matrix& matrix1, int value);
        Matrix dotProduct(Matrix& matrix1, Matrix& matrix2);
        int determinant(Matrix& matrix);
        Matrix inverse(const Matrix &m);
    }
}

#endif