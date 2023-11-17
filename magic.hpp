#ifndef MAGIC_H
#define MAGIC_H

#include <cstring>
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

    namespace strOp {
        std::string toUpperCase(const std::string& str, const std::locale& loc = std::locale());
        std::string toLowerCase(const std::string& str, const std::locale& loc = std::locale());
        std::string trim(const std::string& str);
        std::string trimLeft(const std::string& str);
        std::string trimRight(const std::string& str);
        std::vector<std::string> split(const std::string& str, const std::string& delimiter = " ");
        std::string join(const std::vector<std::string>& strings, const std::string& delimiter = " ");
        std::string substring(const std::string& str, int start, int end);
        std::string replaceOnce(const std::string& str, const std::string& from, const std::string& to);
        std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);
        std::string replaceAllInBetween(const std::string& str, const std::string& from, const std::string& to,
                                        int start, int end);
        bool equalsIgnoreCase(const std::string& str1, const std::string& str2);
        bool startsWith(const std::string& str, const std::string& prefix);
        bool endsWith(const std::string& str, const std::string& suffix);
        bool contains(const std::string& str, const std::string& substr);
        std::string repeat(const std::string& str, int times);
        std::string padLeft(const std::string& str, int width, char paddingChar = ' ');
        std::string padRight(const std::string& str, int width, char paddingChar = ' ');
        std::string padCenter(const std::string& str, int width, char paddingChar = ' ');
        int countOccurrences(const std::string& str, char target);
        std::string removeAllOccurrences(const std::string& str, char target);
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