template <typename T>
static bool emptyp (const ll_stack<T> & s) {
    return (s == NULL);
}

template <typename T>
void init(ll_stack<T> & stack) {
    stack = NULL;
}

template <typename T>
void deinit(ll_stack<T> & stack) {
    while (!emptyp(stack))
        pop(stack);
}

template <typename T>
status push(T el, ll_stack<T> & stack) {
    status res;
    auto * np = new node<T>;
    if (np == NULL)
        res = FAIL;
    else {
        np -> val = el;
        np -> next = stack;
        stack = np;
        res = OK;
    }
    return res;
}

template <typename T>
status top(T &el, const ll_stack<T> & stack) {
    status res;
    if (emptyp(stack))
        res = FAIL;
    else {
        el = stack -> val;
        res = OK;
    }
    return res;
}

template <typename T>
status pop(ll_stack<T> & stack) {
    status res;
    if (emptyp(stack))
        res=FAIL;
    else {
        node<T> *first = stack;
        stack = stack -> next;
        delete first;   // free memory
        res=OK;
    }
    return res;
}

template <typename T>
int size(const ll_stack<T> & stack) {
    int size = 0;
    node<T> *p = stack;
    while (p != NULL) {
        size++;
        p = p -> next;
    }
    return size;
}

template <typename T>
void print(const ll_stack<T> & stack) {
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    node<T> *p = stack;
    while (p != NULL) {
        std::cout << p -> val << " ";
        p = p -> next;
    }
    std::cout << std::endl;
}

template <typename T>
void printBeautified(const ll_stack<T> & stack) {
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    node<T> *p = stack;
    while (p != NULL) {
        int length = std::to_string(p -> val).length();
        std::cout << "┌" << strOp::repeat("─", length + 2) << "┐" << std::endl;
        std::cout << "│" << strOp::padCenter(std::to_string(p -> val), length + 2) << "│" << std::endl;
        std::cout << "└" << strOp::repeat("─", length + 2) << "┘" << std::endl;
        p = p -> next;
    }
    std::cout << std::endl;
}