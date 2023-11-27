template <typename T>
std::string arrayToString(T* arr, int n);

std::string arrayToString(std::string* arr, int n);

template <typename T>
std::string listToString(ds::singly_linked_list<T>& list);

std::string listToString(ds::singly_linked_list<std::string>& list);

TEST_CASE("Algorithms", "[algorithms]") {
    SECTION("Bubblesort") {
        SECTION("Default sorting an array of integers") {
            int arr[] = {5, 4, 3, 2, 1};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::bubbleSort(arr, n);
            std::string result = arrayToString(arr, n);

            std::string expected = "1 2 3 4 5";
            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sorting an array of integers with custom comparison") {
            int arr[] = {23, 65, 12, 3, 9, 1, 0, 5, 7, 8, 2, 4, 6, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::bubbleSort(arr, n, *[](const int &a, const int &b) {
                // Strange sort where even numbers are sorted in descending order and odd numbers are sorted in ascending order
                if (a % 2 == 0 && b % 2 == 0)
                    return a > b;
                 else if (a % 2 == 1 && b % 2 == 1)
                     return a < b;
                else
                    return a < b;
            });

            std::string result = arrayToString(arr, n);

            std::string expected = "65 23 19 17 15 13 12 11 9 7 5 3 1 0 2 4 6 8 10 14 16 18 20";
            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sorting an array of std::strings based on their length") {
            std::string arr[] = {"Hello", "World", "This", "Is", "A", "Test"};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::bubbleSort(arr, n, *[](const std::string &a, const std::string &b) {
                return a.length() > b.length();
            });

            std::string result = arrayToString(arr, n);

            std::string expected = "A Is This Test Hello World";

            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sorting a singly linked list of std::strings based on alphabetical order and then on length") {
            ds::singly_linked_list<std::string> list;

            std::string arr[] = {"Hello", "World", "This", "Is", "A", "Test"};
            int n = sizeof(arr) / sizeof(arr[0]);

            for (int i = 0; i < n; ++i)
                push_back(arr[i], list);

            algo::bubbleSort(list.head, list.tail, *[](const ds::node<std::string> &a, const ds::node<std::string> &b) {
                if (a.val < b.val)
                    return true;
                else if (a.val > b.val)
                    return false;
                else
                    return a.val.length() > b.val.length();
            });

            std::string result = listToString(list);

            std::string expected = "A Hello Is Test This World";

            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sort a list of integeres in ascending order but only up to a certain node (let's say the third)") {
            ds::singly_linked_list<int> list2;

            for (int i = 0; i < 10; ++i)
                push_back(i, list2);

            algo::selectionSort(list2.head, list2.head->next->next->next, *[](const ds::node<int>& a, const ds::node<int>& b) {
                return a.val > b.val;
            });

            std::string result = listToString(list2);

            std::string expected = "3 2 1 0 4 5 6 7 8 9";

            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }
    }

    // Same tests as bubble sort but with selection sort
    SECTION("Selection sort") {
        SECTION("Default sorting an array of integers") {
            int arr[] = {5, 4, 3, 2, 1};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::selectionSort(arr, n);
            std::string result = arrayToString(arr, n);

            std::string expected = "1 2 3 4 5";
            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sorting an array of integers with custom comparison") {
            int arr[] = {23, 65, 12, 3, 9, 1, 0, 5, 7, 8, 2, 4, 6, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::selectionSort(arr, n, *[](const int &a, const int &b) {
                if (a % 2 == 0 && b % 2 == 0)
                    return false;
                else
                    return a > b;
            });

            std::string result = arrayToString(arr, n);

            std::string expected = "0 1 2 3 4 5 6 7 8 9 11 10 12 13 14 15 16 17 18 19 20 23 65";
            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }

        SECTION("Sorting an array of std::strings based on their length") {
            std::string arr[] = {"Hello", "World", "This", "Is", "A", "Test"};
            int n = sizeof(arr) / sizeof(arr[0]);

            algo::selectionSort(arr, n, *[](const std::string &a, const std::string &b) {
                return a.length() > b.length();
            });

            std::string result = arrayToString(arr, n);

            std::string expected = "A Is This Test Hello World";

            REQUIRE_THAT(result, Catch::Matchers::Equals(expected));
        }
    }
}

template <typename T>
std::string arrayToString(T* arr, int n) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        result += std::to_string(arr[i]);
        if (i < n - 1)
            result += " ";
    }
    return result;
}

std::string arrayToString(std::string* arr, int n) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        result += arr[i];
        if (i < n - 1)
            result += " ";
    }
    return result;
}

template <typename T>
std::string listToString(ds::singly_linked_list<T>& list) {
    std::string result;
    while (list.head != nullptr) {
        result += std::to_string(list.head->val);
        if (list.head->next != nullptr)
            result += " ";
        list.head = list.head->next;
    }
    return result;
}

std::string listToString(ds::singly_linked_list<std::string>& list) {
    std::string result;
    while (list.head != nullptr) {
        result += list.head->val;
        if (list.head->next != nullptr)
            result += " ";
        list.head = list.head->next;
    }
    return result;
}