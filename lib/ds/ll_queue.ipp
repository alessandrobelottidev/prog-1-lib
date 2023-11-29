template <typename T>
static bool emptyp (const ll_queue<T> & Q) {
    return (Q.head == NULL);
}

template <typename T>
void init(ll_queue<T> & q) {
    q.head = NULL;
    q.tail = NULL;
}

template <typename T>
void deinit(ll_queue<T> & q) {
    while (!emptyp(q))
        dequeue(q);
}

template <typename T>
status enqueue(T el, ll_queue<T> & q) {
    status res;
    auto * np = new node<T>;
    if (np == NULL)
        res = FAIL;
    else {
        np -> val = el;
        np -> next = NULL;
        if (emptyp(q))
            q.head = np;
        else
            q.tail -> next = np;
        q.tail = np;
        res = OK;
    }
    return res;
}

template <typename T>
status front(T &el, const ll_queue<T> & q) {
    status res;
    if (emptyp(q))
        res = FAIL;
    else {
        el = q.head -> val;
        res = OK;
    }
    return res;
}

template <typename T>
status dequeue(ll_queue<T> & q) {
    status res;
    if (emptyp(q))
        res = FAIL;
    else {
        node<T> *first = q.head;
        q.head = q.head -> next;
        if (q.head == NULL)
            q.tail = NULL;
        delete first;   // free memory
        res = OK;
    }
    return res;
}

template <typename T>
int size(const ll_queue<T> & q) {
    int size = 0;
    node<T> *p = q.head;
    while (p != NULL) {
        size++;
        p = p -> next;
    }
    return size;
}

template <typename T>
void print(const ll_queue<T> & q) {
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    node<T> *p = q.head;
    while (p != NULL) {
        std::cout << p -> val << " ";
        p = p -> next;
    }
    std::cout << std::endl;
}

template <typename T>
void printBeautified(const ll_queue<T> & q) {
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    node<T> *p = q.head;
    while (p != NULL) {
        int length = std::to_string(p -> val).length();
        std::cout << "┌" << strOp::repeat("─", length + 2) << "┐" << " ";
        p = p -> next;
    }
    std::cout << std::endl;
    p = q.head;
    while (p != NULL) {
        int length = std::to_string(p -> val).length();
        std::cout << "│" << strOp::padCenter(std::to_string(p -> val), length + 2) << "│" << " ";
        p = p -> next;
    }
    std::cout << std::endl;
    p = q.head;
    while (p != NULL) {
        int length = std::to_string(p -> val).length();
        std::cout << "└" << strOp::repeat("─", length + 2) << "┘" << " ";
        p = p -> next;
    }
    std::cout << std::endl;
}