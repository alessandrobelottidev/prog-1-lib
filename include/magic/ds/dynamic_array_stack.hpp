template <typename T>
struct dynamic_array_stack
{
    int index;
    T * el;

    dynamic_array_stack() {
        index=0;
        el=new T[dim];
    }

    ~dynamic_array_stack() {
        delete [] el;
    }
};

//template <typename T>
//void init(dynamic_array_stack<T> & stack);
//
//template <typename T>
//void deinit(dynamic_array_stack<T> & stack);

template <typename T>
status push(T el, dynamic_array_stack<T> & stack);

template <typename T>
status top(T &el, const dynamic_array_stack<T> & stack);

template <typename T>
status pop(dynamic_array_stack<T> & stack);

template <typename T>
void print(const dynamic_array_stack<T> & stack);