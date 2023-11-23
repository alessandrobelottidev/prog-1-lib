#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <limits>
#include <iomanip>

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
            std::string top = "====================[ start: " + strOp::toUpperCase(title) + " ]====================";
            log(top,INFO);

            codeBlock();

            std::string bottom = "=====================[ end: " + strOp::toUpperCase(title) + " ]=====================\n\n";
            log(bottom, INFO);
        }
    }

    namespace math {
        bool * sieveOfEratosthenes(int n) {
            // Create a boolean array "isPrime[0..n]" and initialize all entries as true.
            bool * isPrime = new bool[n + 1];
            for (int i = 0; i < n + 1; ++i)
                isPrime[i] = true;

            for (int p = 2; p * p <= n; ++p) {
                // If isPrime[p] is not changed, it's a prime.
                if (isPrime[p]) {
                    // Mark all multiples of p as non-prime.
                    for (int i = p * p; i <= n; i += p) {
                        isPrime[i] = false;
                    }
                }
            }

            return isPrime;
        }
    }

    namespace io {
        template <typename T>
        T read(std::istream& input,
               const std::string& prompt,
               const std::string& errorMessage,
               const std::function<bool(const T&)>& validate) {
            static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");

            T value;
            bool isValid;

            do {
                std::cout << prompt;

                input >> value;

                isValid = false;

                if (input.fail()) {
                    debug::log("Error reading input", debug::ERROR);
                    // Clear input stream and ignore any invalid input
                    input.clear();
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    isValid = validate(value);
                    if (!isValid) {
                        debug::log(errorMessage, debug::ERROR);
                    }
                }
            } while (!isValid);

            return value;
        }

        int showMenu(const std::string& title, const std::string& prompt, const std::vector<std::string>& options,
                     std::istream& input) {
            std::cout << title << std::endl;
            for (int i = 0; i < options.size(); ++i)
                std::cout << i + 1 << ". " << options[i] << std::endl;

            int option;
            bool confirmed;

            do {
                option = read<int>(input, prompt, "Invalid option",
                                   [options](const int &option) { return option >= 1 && option <= options.size(); }
                );

                confirmed = read<char>(
                        input,
                        "Are you sure? (y/n): ",
                        "Invalid input",
                        [](const char& c) {
                            return c == 'y' || c == 'n';
                        }) == 'y';
            } while (!confirmed);

            return option;
        }

        void clearScreen() {
#ifdef _WIN32
            std::system("cls");
#else
            std::cout << "\033[2J\033[1;1H"; // ANSI escape codes for clearing the screen
            //std::system("clear");
#endif
        }
    }

    namespace strOp {
        std::string toUpperCase(const std::string& str, const std::locale& loc) {
            std::string result = str;

            for (char& c : result)
                c = std::toupper(c, loc);

            return result;
        }

        std::string toLowerCase(const std::string& str, const std::locale& loc) {
            std::string result = str;

            for (char& c : result)
                c = std::tolower(c, loc);

            return result;
        }

        std::string trim(const std::string& str) {
            std::string result = str;
            result.erase(0, result.find_first_not_of(' '));
            result.erase(result.find_last_not_of(' ') + 1);
            return result;
        }

        std::string trimLeft(const std::string& str) {
            std::string result = str;
            result.erase(0, result.find_first_not_of(' '));
            return result;
        }

        std::string trimRight(const std::string& str) {
            std::string result = str;
            result.erase(result.find_last_not_of(' ') + 1);
            return result;
        }

        std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
            std::vector<std::string> result;
            std::string s = str;
            size_t pos;
            std::string token;

            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                result.push_back(token);
                s.erase(0, pos + delimiter.length());
            }

            result.push_back(s);
            return result;
        }

        std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
            std::string result;
            for (int i = 0; i < strings.size(); ++i) {
                result += strings[i];
                if (i != strings.size() - 1)
                    result += delimiter;
            }
            return result;
        }

        std::string substring(const std::string& str, int start, int end) {
            std::string result;
            for (int i = start; i < end; ++i)
                result += str[i];
            return result;
        }

        std::string replaceOnce(const std::string& str, const std::string& from, const std::string& to) {
            std::string result = str;
            size_t start_pos = result.find(from);
            if (start_pos != std::string::npos)
                result.replace(start_pos, from.length(), to);
            return result;
        }

        std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
            std::string result = str;
            size_t start_pos = result.find(from);
            while (start_pos != std::string::npos) {
                result.replace(start_pos, from.length(), to);
                start_pos = result.find(from, start_pos + to.length());
            }
            return result;
        }

        std::string replaceAllInBetween(const std::string& str, const std::string& from, const std::string& to,
                                        int start, int end) {
            if (start < 0 || end > str.length())
                throw std::runtime_error("Invalid start or end index");

            std::string result = str;
            size_t start_pos = result.find(from, start);
            while (start_pos != std::string::npos && start_pos < end) {
                result.replace(start_pos, from.length(), to);
                start_pos = result.find(from, start_pos + to.length());
            }
            return result;
        }

        bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
            return toLowerCase(str1) == toLowerCase(str2);
        }

        bool startsWith(const std::string& str, const std::string& prefix) {
            return str.find(prefix) == 0;
        }

        bool endsWith(const std::string& str, const std::string& suffix) {
            return str.rfind(suffix) == (str.length() - suffix.length());
        }

        bool contains(const std::string& str, const std::string& substr) {
            return str.find(substr) != std::string::npos;
        }

        std::string repeat(const std::string& str, int times) {
            std::string result;
            for (int i = 0; i < times; ++i)
                result += str;
            return result;
        }

        std::string padLeft(const std::string& str, int width, char paddingChar) {
            std::string result = str;
            if (result.length() < width)
                result = repeat(std::string(1, paddingChar), width - result.length()) + result;
            return result;
        }

        std::string padRight(const std::string& str, int width, char paddingChar) {
            std::string result = str;
            if (result.length() < width)
                result = result + repeat(std::string(1, paddingChar), width - result.length());
            return result;
        }

        std::string padCenter(const std::string& str, int width, char paddingChar) {
            std::string result = str;
            if (result.length() < width) {
                unsigned long leftPadding = (width - result.length()) / 2;
                unsigned long rightPadding = width - result.length() - leftPadding;
                result = repeat(std::string(1, paddingChar), (int) leftPadding) + result +
                        repeat(std::string(1, paddingChar), (int)rightPadding);
            }
            return result;
        }

        int countOccurrences(const std::string& str, char target) {
            int count = 0;
            for (char c : str)
                if (c == target)
                    count++;
            return count;
        }

        std::string removeAllOccurrences(const std::string& str, char target) {
            std::string result = str;
            for (int i = 0; i < result.length(); ++i)
                if (result[i] == target)
                    result.erase(i--, 1);
            return result;
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

    namespace ds {
        #include "ds/struct_queue.ipp"
        #include "ds/struct_stack.ipp"
        #include "ds/dynamic_array_stack.ipp"
        #include "ds/static_array_stack.ipp"
        #include "ds/dynamic_array_queue.ipp"
        #include "ds/static_array_queue.ipp"
        #include "ds/singly_linked_list.ipp"
    }
}