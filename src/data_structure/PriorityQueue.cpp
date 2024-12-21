#include "PriorityQueue.h"

#include "Router.h"

template<typename T>
void PriorityQueue<T>::enqueue(T value, int priority) {
    ++size;
    array[size].value = value;
    array[size].priority = priority;
}

template<typename T>
void PriorityQueue<T>::dequeue() {
    const uint16_t index = peek();

    for (int i = index; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;
}

template<typename T>
T PriorityQueue<T>::pop() {
    const uint16_t index = peek();
    T tmp = array[index].value;
    for (int i = index; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;
    return tmp;
}

template<typename T>
T PriorityQueue<T>::top() {
    return array[peek()].value;
}

template<typename T>
uint16_t PriorityQueue<T>::peek() {
    int highestPriority = array[0].priority;
    uint16_t index = 0;

    for (int i = index; i <= size; i++) {
        if (highestPriority < array[i].priority) {
            highestPriority = array[i].priority;
            index = i;
        }
    }

    return index;
}

template class PriorityQueue<Router*>;