template <typename T>
static int next(int index, const static_array_queue<T> & q) {
    return (index + 1) % q.size;
}

//template <typename T>
//void init(static_array_queue<T> & q)
//{
//    q.tail = q.head = 0;
//}
//
//template <typename T>
//void deinit(static_array_queue<T> & q)
//{
//    // nothing to do
//}

template <typename T>
static bool emptyp(const static_array_queue<T> & q)
{
    return (q.tail==q.head);
}

template <typename T>
static bool fullp(const static_array_queue<T> & q)
{
    return (next(q.tail,q)==q.head);
}

template <typename T>
status enqueue(T el, static_array_queue<T> & q)
{
    status res;
    if (fullp(q))
        res = FAIL;
    else {
        q.elem[q.tail] = el;
        q.tail = next(q.tail, q);
        res = OK;
    }
    return res;
}

template <typename T>
status front(T & el, const static_array_queue<T> & q)
{
    status res;
    if (emptyp(q))
        res = FAIL;
    else {
        el = q.elem[q.head];
        res = OK;
    }
    return res;
}

template <typename T>
status dequeue(static_array_queue<T> & q)
{
    status res;
    if (emptyp(q))
        res = FAIL;
    else {
        q.head = next(q.head, q);
        res = OK;
    }
    return res;
}

template <typename T>
void print(const static_array_queue<T> & q)
{
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    int i;
    for (i = q.head; i != q.tail; i = next(i, q))
        std::cout << q.elem[i] << " ";
    std::cout << std::endl;
}