#ifndef MAGIC_HPP
#define MAGIC_HPP

#include <iostream>
#include <functional>
#include <vector>

// Type trait to check if a type is a standard type
template <typename T>
struct is_standard_type {
    static constexpr bool value =
            std::is_integral<T>::value ||
            std::is_floating_point<T>::value ||
            std::is_same<T, std::string>::value ||
            std::is_same<T, char>::value ||
            std::is_same<T, wchar_t>::value ||
            std::is_same<T, char16_t>::value ||
            std::is_same<T, char32_t>::value;
};

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

    namespace math {
        bool * sieveOfEratosthenes(int n);
    }

    namespace io {
        template <typename T>
        T read(std::istream& input = std::cin,
               const std::string& prompt = "Enter a value: ",
               const std::string& errorMessage = "Invalid input",
               const std::function<bool(const T&)>& validate = [](const T&) { return true; });

        template <typename T>
        void writeArray(const std::string& title, T *arr, int n, std::ostream& output = std::cout);

        int showMenu(const std::string& title, const std::string& prompt, const std::vector<std::string>& options,
                     std::istream& input = std::cin);

        void clearScreen();
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

    namespace ds {
        enum status {FAIL, OK};

        template <typename T>
        struct node {
            T val;
            node<T> *next;
        };

        static const int dim = 4;

        #include "ds/struct_stack.hpp"
        #include "ds/struct_queue.hpp"
        #include "ds/dynamic_array_stack.hpp"
        #include "ds/static_array_stack.hpp"
        #include "ds/dynamic_array_queue.hpp"
        #include "ds/static_array_queue.hpp"
        #include "ds/singly_linked_list.hpp"
    }

    namespace algo {
        template <typename T>
        bool compare(const T& a, const T& b);

        template <typename T>
        bool compareNodes(const ds::node<T>& a, const ds::node<T>& b);

        template <typename T>
        void swap(T& a, T& b);

        template <typename T>
        void swapNodes(ds::node<T> *a, ds::node<T> *b);

        /*
         * Name: Bubble sort
         * Time complexity: Ω(n), Θ(n^2), O(n^2)
         * Space complexity: O(1)
         */
        template <typename T>
        void bubbleSort(T *arr, int n, bool (*compare)(const T&, const T&) = algo::compare);

        template <typename T>
        void bubbleSort(ds::node<T> * start, ds::node<T> * end, bool (*compare)(const ds::node<T>&, const ds::node<T>&) = algo::compareNodes);

        /*
         * Name: Insertion sort
         * Time complexity: Ω(n), Θ(n^2), O(n^2)
         * Space complexity: O(1)
         */
        template <typename T>
        void insertionSort(T *arr, int n, bool (*compare)(const T&, const T&) = algo::compare);

        template <typename T>
        void insertionSort(ds::node<T> * start, ds::node<T> * end, bool (*compare)(const ds::node<T>&, const ds::node<T>&) = algo::compareNodes);

        /*
         * Name: Selection sort
         * Time complexity: Ω(n^2), Θ(n^2), O(n^2)
         * Space complexity: O(1)
         */
        template <typename T>
        void selectionSort(T *arr, int n, bool (*compare)(const T&, const T&) = algo::compare);

        template <typename T>
        void selectionSort(ds::node<T> * start, ds::node<T> * end, bool (*compare)(const ds::node<T>&, const ds::node<T>&) = algo::compareNodes);

        /*
         * Name: Merge sort
         * Time complexity: Ω(n log(n)), Θ(n log(n)), O(n log(n))
         * Space complexity: O(n)
         */
        template <typename T>
        void mergeSort(T *arr, int n, bool (*compare)(const T&, const T&) = algo::compare);

        template <typename T>
        void mergeSort(ds::node<T> * start, ds::node<T> * end, bool (*compare)(const ds::node<T>&, const ds::node<T>&) = algo::compareNodes);

        /*
         * Name: Quick sort
         * Time complexity: Ω(n log(n)), Θ(n log(n)), O(n^2)
         * Space complexity: O(log(n))
         */
        template <typename T>
        void quickSort(T *arr, int n, bool (*compare)(const T&, const T&) = algo::compare);

        template <typename T>
        void quickSort(ds::node<T> * start, ds::node<T> * end, bool (*compare)(const ds::node<T>&, const ds::node<T>&) = algo::compareNodes);

        /*
         * Name: Binary search
         * Time complexity: Ω(1), Θ(log(n)), O(log(n))
         * Space complexity: O(1)
         */
        template <typename T>
        int binarySearch(T *arr, int n, T target);

        template <typename T>
        int binarySearch(ds::node<T> * start, ds::node<T> * end, T target);
    }
}

#include "magic.ipp"

#endif