#ifndef STACK_H
#define STACK_H
#include <cstddef>

template<typename T, typename SIZE_TYPE=size_t>
class Stack {
public:
    Stack();

    explicit Stack(SIZE_TYPE size);

    Stack(const Stack<T, SIZE_TYPE> &other);

    Stack<T, SIZE_TYPE> &operator=(const Stack<T, SIZE_TYPE> &other);

    ~Stack();

    void push(T x);

    bool isEmpty();

    T top();

    T pop();

private:
    SIZE_TYPE _size;
    T *array;
    SIZE_TYPE tailPointer;

    void resize();
};


#endif //STACK_H
