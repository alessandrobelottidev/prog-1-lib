#include "magic.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <vector>

namespace magic {
    namespace debug {
        void log(const std::string& message, LogLevel level) {
            std::string prefix;
            std::string color;

            switch (level) {
                case DEBUG:
                    prefix = "[DEBUG] ";
                    color = ANSI_BLUE;
                    break;
                case INFO:
                    prefix = "[INFO] ";
                    color = ANSI_GREEN;
                    break;
                case WARNING:
                    prefix = "[WARNING] ";
                    color = ANSI_YELLOW;
                    break;
                case ERROR:
                    prefix = "[ERROR] ";
                    color = ANSI_RED;
                    break;
                default:
                    prefix = "[LOG] ";
                    color = ANSI_RESET;
            }

            std::cout << color << prefix << message << ANSI_RESET << std::endl;
        }

        // Function registry to map function names to actual functions
        std::map<std::string, std::function<void(const std::vector<std::string>&)>> functionRegistry;

        void registerFunction(const std::string& functionName,
                              std::function<void(const std::vector<std::string>&)> function) {
            functionRegistry[functionName] = std::move(function);
        }

        void callFunctionByName(const std::string& functionName, const std::vector<std::string>& arguments) {
            if (functionRegistry.find(functionName) != functionRegistry.end()) {
                functionRegistry[functionName](arguments);
            } else {
                log("Function not found: " + functionName, ERROR);
            }
        }

        void logAndCall(const std::string& title,
                        const std::string& functionName,
                        std::function<void(const std::vector<std::string>&)> function,
                        const std::vector<std::string>& arguments) {
            log(title, INFO);
            registerFunction(functionName, std::move(function));
            callFunctionByName(functionName, arguments);
        }
    }

    namespace matrix {
        Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
            data = new int *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
            }
        }

        Matrix::Matrix(const Matrix &other) : rows(other.rows), cols(other.cols) {
            data = new int *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }
        }

        Matrix::~Matrix() {
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;
        }

        Matrix &Matrix::operator=(const Matrix &other) {
            if (this == &other) {
                return *this; // Self-assignment check
            }

            // Deallocate existing data
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;

            // Copy data from 'other' to this
            rows = other.rows;
            cols = other.cols;
            data = new int *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }

            return *this;
        }

        void Matrix::set(int row, int col, int value) const {
            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                data[row][col] = value;
            }
        }

        int Matrix::get(int row, int col) const {
            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                return data[row][col];
            } else {
                // Return a default value or handle the error as needed
                throw std::runtime_error("Couldn't get a value at this position row:" + std::to_string(row) + ", col:" + std::to_string(col));
            }
        }

        __attribute__((unused)) bool Matrix::isSquared() const {
            return rows == cols;
        }

        void Matrix::print() const {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    std::cout << data[i][j] << " ";
                std::cout << std::endl;
            }
        }

        void transpose(Matrix& matrix) {
            int newRows = matrix.cols;
            int newCols = matrix.rows;
            Matrix transposed(newRows, newCols);

            for (int i = 0; i < matrix.rows; ++i)
                for (int j = 0; j < matrix.cols; ++j)
                    transposed.set(j, i, matrix.get(i, j));

            matrix = transposed;
        }
    }
}