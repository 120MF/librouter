#include <stdexcept>

#include "Router.h"
#include "Stack.h"
#include "utils/MaxValue.hpp"

template<typename T, typename SIZE_TYPE>
Stack<T, SIZE_TYPE>::Stack() {
    _size = 1;
    array = new T[_size];
    tailPointer = 0;
}

template<typename T, typename SIZE_TYPE>
Stack<T, SIZE_TYPE>::Stack(SIZE_TYPE size): _size(size) {
    array = new T[_size];
    tailPointer = 0;
}

template<typename T, typename SIZE_TYPE>
Stack<T, SIZE_TYPE>::Stack(const Stack<T, SIZE_TYPE> &other) {
    _size = other._size;
    tailPointer = other.tailPointer;
    array = new T[_size];
    std::copy(other.array, other.array + _size, array);
}

template<typename T, typename SIZE_TYPE>
Stack<T, SIZE_TYPE> &Stack<T, SIZE_TYPE>::operator=(const Stack<T, SIZE_TYPE> &other) {
    if (this != &other) {
        delete[] array;
        _size = other._size;
        tailPointer = other.tailPointer;
        array = new T[_size];
        std::copy(other.array, other.array + _size, array);
    }
    return *this;
}

template<typename T, typename SIZE_TYPE>
Stack<T, SIZE_TYPE>::~Stack() {
    delete[] array;
}

template<typename T, typename SIZE_TYPE>
void Stack<T, SIZE_TYPE>::push(T x) {
    if (tailPointer == _size - 1) resize();
    array[tailPointer++] = x;
}

template<typename T, typename SIZE_TYPE>
inline bool Stack<T, SIZE_TYPE>::isEmpty() {
    return tailPointer == 0;
}

template<typename T, typename SIZE_TYPE>
T Stack<T, SIZE_TYPE>::top() {
    return array[tailPointer - 1];
}

template<typename T, typename SIZE_TYPE>
T Stack<T, SIZE_TYPE>::pop() {
    if (isEmpty()) throw std::invalid_argument("no element in the stack");
    return array[--tailPointer];
}

template<typename T, typename SIZE_TYPE>
void Stack<T, SIZE_TYPE>::resize() {
    SIZE_TYPE newSize = _size * 2;
    if (newSize > MaxValue<SIZE_TYPE>::value) throw std::invalid_argument("stack overflowed");
    T *newArray = new T[newSize];

    std::copy(array, array + _size, newArray);
    _size = newSize;
    delete[] array;
    array = newArray;
}

template class Stack<int, size_t>;
template class Stack<Router *, size_t>;
