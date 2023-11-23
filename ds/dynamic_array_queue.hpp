template <typename T>
struct dynamic_array_queue
{
    int head, tail;
    T * elem;
    int size;

    dynamic_array_queue() {
        head = 0;
        tail = 0;
        size = 10;
        elem = new T[size];
    }

    ~dynamic_array_queue() {
        delete [] elem;
    }
};

//template <typename T>
//void init(dynamic_array_queue<T> & q);
//
//template <typename T>
//void deinit(dynamic_array_queue<T> & q);

template <typename T>
status enqueue(T el, dynamic_array_queue<T> & q);

template <typename T>
status front(T & el, const dynamic_array_queue<T> & q);

template <typename T>
status dequeue(dynamic_array_queue<T> & q);

template <typename T>
void print(const dynamic_array_queue<T> & q);