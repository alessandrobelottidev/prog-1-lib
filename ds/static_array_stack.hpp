template <typename T>
struct static_array_stack
{
    int index;
    T el[dim];

    static_array_stack() {
        index=0;
    }

    ~static_array_stack() {
        // nothing to do
    }
};

//template <typename T>
//void init(static_array_stack<T> & stack);
//
//template <typename T>
//void deinit(static_array_stack<T> & stack);

template <typename T>
status push(T el, static_array_stack<T> & stack);

template <typename T>
status top(T &el, const static_array_stack<T> & stack);

template <typename T>
status pop(static_array_stack<T> & stack);

template <typename T>
void print(const static_array_stack<T> & stack);