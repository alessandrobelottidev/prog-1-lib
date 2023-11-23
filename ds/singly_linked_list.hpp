template <typename T>
struct singly_linked_list {
    node<T> * head;
    node<T> * tail;

    singly_linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    ~singly_linked_list() {
        node<T> * current = head;
        while (current) {
            node<T> * next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};

//template <typename T>
//void init(singly_linked_list<T> & list);
//
//template <typename T>
//void deinit(singly_linked_list<T> & list);

/*
begin() – begin() function returns an iterator pointing to the first element of the list.
end() – end() function returns an iterator pointing to the theoretical last element which follows the last element.
 */

template <typename T>
status push_front(T el, singly_linked_list<T> & list);

template <typename T>
status push_back(T el, singly_linked_list<T> & list);

template <typename T>
status pop_front(singly_linked_list<T> & list);

template <typename T>
status pop_back(singly_linked_list<T> & list);

template <typename T>
status insert(T el, int pos, singly_linked_list<T> & list);

template <typename T>
status remove(int pos, singly_linked_list<T> & list);

template <typename T>
status front(T & el, const singly_linked_list<T> & list);

template <typename T>
status back(T & el, const singly_linked_list<T> & list);

template <typename T>
int size(const singly_linked_list<T> & list);

template <typename T>
void print(const singly_linked_list<T> & list);

template <typename T>
struct LinkedListIterator {
    node<T>* current;

    // Overload the ++ operator to move the iterator to the next node
    LinkedListIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    // Overload the != operator to check if two iterators are not equal
    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }

    // Overload the * operator to get the data of the current node
    T operator*() const {
        return current->val;
    }
};

template <typename T>
LinkedListIterator<T> begin(const singly_linked_list<T>& list);

template <typename T>
LinkedListIterator<T> end(const singly_linked_list<T>& list);