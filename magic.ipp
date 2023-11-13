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

        void logBlock(const std::string& title, const std::function<void()>& codeBlock) {
            std::string top = "====================[ start: " + manipulation::toUpperCase(title) + " ]====================";
            log(top,INFO);

            codeBlock();

            std::string bottom = "=====================[ end: " + manipulation::toUpperCase(title) + " ]=====================\n\n";
            log(bottom, INFO);
        }
    }

    namespace matrix {
        template <typename T>
        Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
            data = new T *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new T[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = 0;
            }
        }

        template <typename T>
        Matrix<T>::Matrix(int rows, int cols, T **data) {
            this->rows = rows;
            this->cols = cols;
            this->data = data;
        }

        template <typename T>
        Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), cols(other.cols) {
            data = new T *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new T[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }
        }

        template <typename T>
        Matrix<T>::~Matrix() {
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;
        }

        template <typename T>
        Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
            if (this == &other)
                return *this; // Self-assignment check

            // Deallocate existing data
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;

            // Copy data from 'other' to this
            rows = other.rows;
            cols = other.cols;
            data = new T *[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new T[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }

            return *this;
        }

        template <typename T>
        void Matrix<T>::set(int row, int col, T value) const {
            if (row >= 0 && row < rows && col >= 0 && col < cols)
                data[row][col] = value;
            else
                throw std::runtime_error("Couldn't set a value at this position row:" + std::to_string(row) + ", col:" + std::to_string(col));
        }

        template <typename T>
        T Matrix<T>::get(int row, int col) const {
            if (row >= 0 && row < rows && col >= 0 && col < cols)
                return data[row][col];
            else
                // Return a default value or handle the error as needed
                throw std::runtime_error("Couldn't get a value at this position row:" + std::to_string(row) + ", col:" + std::to_string(col));
        }

        template <typename T>
        bool Matrix<T>::isSquared() const {
            return rows == cols;
        }

        template <typename T>
        void Matrix<T>::print(bool lastSepIncluded) const {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (j == cols - 1 && !lastSepIncluded)
                        std::cout << data[i][j];
                    else
                        std::cout << data[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        template <typename T>
        void transpose(Matrix<T>& m) {
            int newRows = m.cols;
            int newCols = m.rows;
            Matrix<T> transposed(newRows, newCols);

            for (int i = 0; i < m.rows; ++i)
                for (int j = 0; j < m.cols; ++j)
                    transposed.set(j, i, m.get(i, j));

            m = transposed;
        }

        template <typename T>
        void sum(Matrix<T>& m, T value) {
            for (int i = 0; i < m.rows; ++i)
                for (int j = 0; j < m.cols; ++j)
                    m.set(i, j, m.get(i, j) + value);
        }

        template <typename T>
        void sum(Matrix<T>& m1, Matrix<T>& m2) {
            for (int i = 0; i < m1.rows; ++i)
                for (int j = 0; j < m1.cols; ++j)
                    m1.set(i, j, m1.get(i, j) + m2.get(i, j));
        }

        template <typename T>
        void subtract(Matrix<T>& m1, Matrix<T>& m2) {
            for (int i = 0; i < m1.rows; ++i)
                for (int j = 0; j < m1.cols; ++j)
                    m1.set(i, j, m1.get(i, j) - m2.get(i, j));
        }

        template <typename T>
        void scalarProduct(Matrix<T>& m, T value) {
            for (int i = 0; i < m.rows; ++i)
                for (int j = 0; j < m.cols; ++j)
                    m.set(i, j, m.get(i, j) * value);
        }

        template <typename T>
        Matrix<T> dotProduct(Matrix<T>& m1, Matrix<T>& m2) {
            if (m1.cols != m2.rows)
                throw std::runtime_error("Matrix dimensions don't match for dot product");

            Matrix<T> result(m1.rows, m2.cols);

            for (int i = 0; i < m1.rows; ++i)
                for (int j = 0; j < m2.cols; ++j)
                    for (int k = 0; k < m1.cols; ++k)
                        result.set(i, j, result.get(i, j) + m1.get(i, k) * m2.get(k, j));

            return result;
        }

        template <typename T>
        int determinant(Matrix<T>& m) {
            if (!m.isSquared())
                throw std::runtime_error("Matrix is not squared");

            if (m.rows == 1)
                return m.get(0, 0);

            if (m.rows == 2)
                return m.get(0, 0) * m.get(1, 1) - m.get(0, 1) * m.get(1, 0);

            int finalX = 0;
            int finalY = 0;
            for(int i = 0; i < m.rows; i++) {
                int x = 1;
                int y = 1;
                for (int j=0; j < m.rows; j++) {
                    x *= m.get(j, (i+j) % m.rows);
                    y *= m.get(m.rows - 1 - j, (i+j) % m.rows);
                }
                finalX += x;
                finalY += y;
            }

            int det = finalX - finalY;
            return det;
        }

        template <typename T>
        Matrix<T> inverse(Matrix<T>& m) {
            if (!m.isSquared())
                throw std::runtime_error("Matrix is not squared");

            if (determinant(m) == 0)
                throw std::runtime_error("Matrix is not invertible");

            int n = m.rows;

            // Creating a temporary array to hold the expanded array [m | I]
            Matrix<T> augmentedMatrix(n, 2 * n);

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
            Matrix<T> inverseMatrix(n, n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    inverseMatrix.set(i, j, augmentedMatrix.get(i, j + n));

            return inverseMatrix;
        }
    }
}