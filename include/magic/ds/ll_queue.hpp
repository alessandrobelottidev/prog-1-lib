template <typename T>
struct ll_queue
{
    node<T> * tail;
    node<T> * head;
};

template <typename T>
void init(ll_queue<T> & q);

template <typename T>
void deinit(ll_queue<T> & q);

template <typename T>
status enqueue(T el, ll_queue<T> & q);

template <typename T>
status front(T & el, const ll_queue<T> & q);

template <typename T>
status dequeue(ll_queue<T> & q);

template <typename T>
int size(const ll_queue<T> & q);

template <typename T>
void print(const ll_queue<T> & q);

template <typename T>
void printBeautified(const ll_queue<T> & q);