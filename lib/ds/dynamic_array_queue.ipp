template <typename T>
static int next(int index, const dynamic_array_queue<T> & q) {
    return (index + 1) % q.size;
}

//template <typename T>
//void init(dynamic_array_queue<T> & q)
//{
//    q.tail = q.head = 0;
//    q.size = dim + 1;
//    q.elem = new int[q.size];
//}
//
//template <typename T>
//void deinit(dynamic_array_queue<T> & q)
//{
//    delete [] q.elem;
//}

template <typename T>
static bool emptyp(const dynamic_array_queue<T> & q)
{
    return (q.tail==q.head);
}

template <typename T>
static bool fullp(const dynamic_array_queue<T> & q)
{
    return (next(q.tail,q)==q.head);
}

template <typename T>
status enqueue(T el, dynamic_array_queue<T> & q)
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
status front(T & el, const dynamic_array_queue<T> & q)
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
status dequeue(dynamic_array_queue<T> & q)
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
void print(const dynamic_array_queue<T> & q)
{
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    int i;
    for (i = q.head; i != q.tail; i = next(i, q))
        std::cout << q.elem[i] << " ";
    std::cout << std::endl;
}