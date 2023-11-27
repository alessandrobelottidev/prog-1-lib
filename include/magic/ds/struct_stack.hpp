template <typename T>
using struct_stack = node<T>*;


template <typename T>
void init(struct_stack<T> & stack);

template <typename T>
void deinit(struct_stack<T> & stack);

template <typename T>
status push(T el, struct_stack<T> & stack);

template <typename T>
status top(T &el, const struct_stack<T> & stack);

template <typename T>
status pop(struct_stack<T> & stack);

template <typename T>
int size(const struct_stack<T> & stack);

template <typename T>
void print(const struct_stack<T> & stack);

template <typename T>
void printBeautified(const struct_stack<T> & stack);