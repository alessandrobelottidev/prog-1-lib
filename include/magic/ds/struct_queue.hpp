template <typename T>
struct struct_queue
{
    node<T> * tail;
    node<T> * head;
};

template <typename T>
void init(struct_queue<T> & q);

template <typename T>
void deinit(struct_queue<T> & q);

template <typename T>
status enqueue(T el, struct_queue<T> & q);

template <typename T>
status front(T & el, const struct_queue<T> & q);

template <typename T>
status dequeue(struct_queue<T> & q);

template <typename T>
int size(const struct_queue<T> & q);

template <typename T>
void print(const struct_queue<T> & q);

template <typename T>
void printBeautified(const struct_queue<T> & q);