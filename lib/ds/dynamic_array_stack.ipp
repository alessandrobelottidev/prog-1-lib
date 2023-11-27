template <typename T>
static bool emptyp (const dynamic_array_stack<T> & s)
{
    return (s.index==0);
}

template <typename T>
static bool fullp (const dynamic_array_stack<T> & s)
{
    return (s.index==dim);
}

//template <typename T>
//void init(dynamic_array_stack<T> & s)
//{
//    s.index=0;
//    s.el=new T[dim];
//}
//
//template <typename T>
//void deinit(dynamic_array_stack<T> & s)
//{
//    delete [] s.el;
//}

template <typename T>
status push(T el, dynamic_array_stack<T> & s)
{
    status res;
    if (fullp(s))
        res=FAIL;
    else {
        s.el[s.index]=el;
        s.index++;
        res=OK;
    }
    return res;
}

template <typename T>
status top(T &el, const dynamic_array_stack<T> & s)
{
    status res;
    if (emptyp(s))
        res=FAIL;
    else {
        el=s.el[s.index-1];
        res=OK;
    }
    return res;
}

template <typename T>
status pop(dynamic_array_stack<T> & s)
{
    status res;
    if (emptyp(s))
        res=FAIL;
    else {
        s.index--;
        res=OK;
    }
    return res;
}

template <typename T>
void print(const dynamic_array_stack<T> & s)
{
    static_assert(is_standard_type<T>::value, "Non-standard type used in read function. Use standard types only.");
    for (int i=0; i<s.index; i++)
        std::cout << s.el[i] << " ";
    std::cout << std::endl;
}