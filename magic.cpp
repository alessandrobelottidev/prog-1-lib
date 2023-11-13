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
            if (functionRegistry.find(functionName) != functionRegistry.end())
                functionRegistry[functionName](arguments);
            else
                log("Function not found: " + functionName, ERROR);
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
                for (int j = 0; j < cols; j++)
                    data[i][j] = 0;
            }
        }

        Matrix::Matrix(int rows, int cols, int **data) {
            this->rows = rows;
            this->cols = cols;
            this->data = data;
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
            if (this == &other)
                return *this; // Self-assignment check

            // Deallocate existing data
            for (int i = 0; i < rows; i++)
                delete[] data[i];
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
            if (row >= 0 && row < rows && col >= 0 && col < cols)
                data[row][col] = value;
        }

        int Matrix::get(int row, int col) const {
            if (row >= 0 && row < rows && col >= 0 && col < cols)
                return data[row][col];
            else
                // Return a default value or handle the error as needed
                throw std::runtime_error("Couldn't get a value at this position row:" + std::to_string(row) + ", col:" + std::to_string(col));
        }

        bool Matrix::isSquared() const {
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

        void sum(Matrix &matrix1, int value) {
            for (int i = 0; i < matrix1.rows; ++i)
                for (int j = 0; j < matrix1.cols; ++j)
                    matrix1.set(i, j, matrix1.get(i, j) + value);
        }

        void sum(Matrix &matrix1, Matrix &matrix2) {
            for (int i = 0; i < matrix1.rows; ++i)
                for (int j = 0; j < matrix1.cols; ++j)
                    matrix1.set(i, j, matrix1.get(i, j) + matrix2.get(i, j));
        }

        void subtract(Matrix &matrix1, Matrix &matrix2) {
            for (int i = 0; i < matrix1.rows; ++i)
                for (int j = 0; j < matrix1.cols; ++j)
                    matrix1.set(i, j, matrix1.get(i, j) - matrix2.get(i, j));
        }

        void scalarProduct(Matrix &matrix1, int value) {
            for (int i = 0; i < matrix1.rows; ++i)
                for (int j = 0; j < matrix1.cols; ++j)
                    matrix1.set(i, j, matrix1.get(i, j) * value);
        }

        Matrix dotProduct(Matrix &matrix1, Matrix &matrix2) {
            if (matrix1.cols != matrix2.rows)
                throw std::runtime_error("Matrix dimensions don't match for dot product");

            Matrix result(matrix1.rows, matrix2.cols);

            for (int i = 0; i < matrix1.rows; ++i)
                for (int j = 0; j < matrix2.cols; ++j)
                    for (int k = 0; k < matrix1.cols; ++k)
                        result.set(i, j, result.get(i, j) + matrix1.get(i, k) * matrix2.get(k, j));

            return result;
        }

        int determinant(Matrix& matrix) {
            if (!matrix.isSquared())
                throw std::runtime_error("Matrix is not squared");

            if (matrix.rows == 1)
                return matrix.get(0, 0);

            if (matrix.rows == 2)
                return matrix.get(0, 0) * matrix.get(1, 1) - matrix.get(0, 1) * matrix.get(1, 0);

            int finalX = 0;
            int finalY = 0;
            for(int i = 0; i < matrix.rows; i++) {
                int x = 1;
                int y = 1;
                for (int j=0; j < matrix.rows; j++) {
                    x *= matrix.get(j, (i+j) % matrix.rows);
                    y *= matrix.get(matrix.rows - 1 - j, (i+j) % matrix.rows);
                }
                finalX += x;
                finalY += y;
            }

            int det = finalX - finalY;
            return det;
        }

        Matrix inverse(const Matrix &m) {
            if (!m.isSquared())
                throw std::runtime_error("Matrix is not squared");

            int n = m.rows;

            // Creating a temporary array to hold the expanded array [m | I]
            Matrix augmentedMatrix(n, 2 * n);

            // Initialize the expanded matrix with the original matrix followed by the identity matrix
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) {
                    augmentedMatrix.set(i, j, m.get(i, j));
                    augmentedMatrix.set(i, j + n, i == j ? 1 : 0); // Identity matrix
                }

            // Reduction of the left part of the enlarged matrix to a reduced Gaussian shape
            for (int i = 0; i < n; ++i) {
                // Find the column with the maximum element in absolute value in the current column
                int maxRowIndex = i;
                for (int k = i + 1; k < n; ++k)
                    if (std::abs(augmentedMatrix.get(k, i)) > std::abs(augmentedMatrix.get(maxRowIndex, i)))
                        maxRowIndex = k;

                // Swap rows to have the maximum element at the current position
                for (int k = 0; k < 2 * n; ++k)
                    std::swap(augmentedMatrix.data[i][k], augmentedMatrix.data[maxRowIndex][k]);

                // Collapse the current row
                double pivot = augmentedMatrix.get(i, i);
                for (int k = 0; k < 2 * n; ++k)
                    augmentedMatrix.set(i, k, augmentedMatrix.get(i, k) / pivot);

                // Reduce the other lines
                for (int k = 0; k < n; ++k)
                    if (k != i) {
                        double factor = augmentedMatrix.get(k, i);
                        for (int l = 0; l < 2 * n; ++l)
                            augmentedMatrix.set(k, l, augmentedMatrix.get(k, l) - factor * augmentedMatrix.get(i, l));
                    }
            }

            // Extract the right part of the enlarged matrix, which should be the inverse matrix
            Matrix inverseMatrix(n, n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    inverseMatrix.set(i, j, augmentedMatrix.get(i, j + n));

            return inverseMatrix;
        }
    }
}