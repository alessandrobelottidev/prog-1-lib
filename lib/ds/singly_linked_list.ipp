//template <typename T>
//void init(singly_linked_list<T> & list)
//{
//    list.head = nullptr;
//    list.tail = nullptr;
//}
//
//template <typename T>
//void deinit(singly_linked_list<T> & list)
//{
//    node<T> * current = list.head;
//    while (current) {
//        node<T> * next = current->next;
//        delete current;
//        current = next;
//    }
//    list.head = nullptr;
//    list.tail = nullptr;
//}

template <typename T>
status push_front(T el, singly_linked_list<T> & list)
{
    node<T> * new_node = new node<T>{el, list.head};
    list.head = new_node;
    if (!list.tail) {
        list.tail = new_node;
    }
    return status::OK;
}

template <typename T>
status push_back(T el, singly_linked_list<T> & list)
{
    node<T> * new_node = new node<T>{el, nullptr};
    
    if (!list.head) {
        list.head = new_node;
    }
    if (list.tail) {
        list.tail->next = new_node;
    }
    list.tail = new_node;
    return status::OK;
}

template <typename T>
status pop_front(singly_linked_list<T> & list)
{
    if (!list.head) {
        return status::FAIL;
    }
    node<T> * old_head = list.head;
    list.head = list.head->next;
    if (!list.head) {
        list.tail = nullptr;
    }
    delete old_head;
    return status::OK;
}

template <typename T>
status pop_back(singly_linked_list<T> & list)
{
    if (!list.head) {
        return status::FAIL;
    }
    if (list.head == list.tail) {
        delete list.head;
        list.head = nullptr;
        list.tail = nullptr;
        return status::OK;
    }
    node<T> * current = list.head;
    while (current->next != list.tail) {
        current = current->next;
    }
    delete list.tail;
    list.tail = current;
    list.tail->next = nullptr;
    return status::OK;
}

template <typename T>
status insert(T el, int pos, singly_linked_list<T> & list)
{
    if (pos < 0) {
        return status::FAIL;
    }
    if (pos == 0) {
        return push_front(el, list);
    }
    node<T> * current = list.head;
    while (pos > 1 && current) {
        current = current->next;
        pos--;
    }
    if (!current) {
        return status::FAIL;
    }
    node<T> * new_node = new node<T>;
    new_node->val = el;
    new_node->next = current->next;
    current->next = new_node;
    if (!new_node->next) {
        list.tail = new_node;
    }
    return status::OK;
}

template <typename T>
status remove(int pos, singly_linked_list<T> & list)
{
    if (pos < 0) {
        return status::FAIL;
    }
    if (pos == 0) {
        return pop_front(list);
    }
    node<T> * current = list.head;
    while (pos > 1 && current) {
        current = current->next;
        pos--;
    }
    if (!current || !current->next) {
        return status::FAIL;
    }
    node<T> * old_node = current->next;
    current->next = current->next->next;
    if (!current->next) {
        list.tail = current;
    }
    delete old_node;
    return status::OK;
}

template <typename T>
status front(T & el, const singly_linked_list<T> & list)
{
    if (!list.head) {
        return status::FAIL;
    }
    el = list.head->val;
    return status::OK;
}

template <typename T>
status back(T & el, const singly_linked_list<T> & list)
{
    if (!list.tail) {
        return status::FAIL;
    }
    el = list.tail->val;
    return status::OK;
}

template <typename T>
int size(const singly_linked_list<T> & list)
{
    int size = 0;
    node<T> * current = list.head;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}

template <typename T>
void print(const singly_linked_list<T> & list)
{
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
//    node<T> * current = list.head;
//    while (current) {
//        std::cout << current->val << " ";
//        current = current->next;
//    }
    for (auto it = begin(list); it != end(list); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
LinkedListIterator<T> begin(const singly_linked_list<T>& list)
{
    return LinkedListIterator<T>{list.head};
}

template <typename T>
LinkedListIterator<T> end(const singly_linked_list<T>& list)
{
    return LinkedListIterator<T>{nullptr};
}