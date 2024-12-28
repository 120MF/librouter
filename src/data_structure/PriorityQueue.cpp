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
    if (size < 0) return;
    const uint16_t index = peek();

    for (int i = index; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;
}

template<typename T>
T PriorityQueue<T>::pop() {
    if (size < 0) throw std::invalid_argument("no element in the queue");
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
    if (size < 0) throw std::invalid_argument("no element in the queue");
    return array[peek()].value;
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const {
    return size < 0;
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

template class PriorityQueue<Router *>;
template class PriorityQueue<int>;
template class PriorityQueue<uint64_t>;
