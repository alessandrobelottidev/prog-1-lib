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
        void logBlock(const std::string& title, const std::function<void()>& codeBlock);
    }

    namespace manipulation {
        std::string toUpperCase(const std::string& str, const std::locale& loc = std::locale()) {
            std::string result = str;

            for (char& c : result)
                c = std::toupper(c, loc);

            return result;
        }
    }

    namespace matrix {
        template <typename T>
        struct Matrix {
            static_assert(std::is_arithmetic<T>::value, "Matrix can only be instantiated with arithmetic types");

            int rows{};
            int cols{};
            T** data;

            Matrix(int rows, int cols); // Default constructor
            Matrix(int rows, int cols, T **data); // Constructor with data
            Matrix(const Matrix<T> &other); // Copy constructor for deep
            ~Matrix(); // Destructor to free memory

            Matrix<T>& operator=(const Matrix<T> &other); // Assignment operator for deep copy

            void set(int row, int col, T value) const;
            T get(int row, int col) const;

            bool isSquared() const;
            void print(bool lastSepIncluded = false) const;
        };

        template <typename T>
        void transpose(Matrix<T>& m);

        template <typename T>
        void sum(Matrix<T>& m1, T value);

        template <typename T>
        void sum(Matrix<T>& m1, Matrix<T>& m2);

        template <typename T>
        void subtract(Matrix<T>& m1, Matrix<T>& m2);

        template <typename T>
        void scalarProduct(Matrix<T>& m, T value);

        template <typename T>
        Matrix<T> dotProduct(Matrix<T>& m1, Matrix<T>& m2);

        template <typename T>
        int determinant(Matrix<T>& m);

        template <typename T>
        Matrix<T> inverse(Matrix<T>& m);
    }
}

#include "magic.ipp"

#endif