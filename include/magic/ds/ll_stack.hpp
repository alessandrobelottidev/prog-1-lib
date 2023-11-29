template <typename T>
using ll_stack = node<T>*;


template <typename T>
void init(ll_stack<T> & stack);

template <typename T>
void deinit(ll_stack<T> & stack);

template <typename T>
status push(T el, ll_stack<T> & stack);

template <typename T>
status top(T &el, const ll_stack<T> & stack);

template <typename T>
status pop(ll_stack<T> & stack);

template <typename T>
int size(const ll_stack<T> & stack);

template <typename T>
void print(const ll_stack<T> & stack);

template <typename T>
void printBeautified(const ll_stack<T> & stack);