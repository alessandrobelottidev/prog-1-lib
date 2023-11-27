template <typename T>
struct static_array_queue
{
    int head, tail;
    T elem[dim + 1];
    int size = dim + 1;

    static_array_queue() {
        head = tail = 0;
    }

    ~static_array_queue() {
        // nothing to do
    }
};

//template <typename T>
//void init(static_array_queue<T> & q);
//
//template <typename T>
//void deinit(static_array_queue<T> & q);

template <typename T>
status enqueue(T el, static_array_queue<T> & q);

template <typename T>
status front(T & el, const static_array_queue<T> & q);

template <typename T>
status dequeue(static_array_queue<T> & q);

template <typename T>
void print(const static_array_queue<T> & q);