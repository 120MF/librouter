#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <cstdint>

constexpr uint16_t MAXN = UINT16_MAX;

template<typename T>
struct item {
    T value;
    int priority;
};
template<typename T>
class PriorityQueue {
public:
    void enqueue(T value, int priority);
    void dequeue();
    T pop();
    T top();

    uint16_t peek();

private:
    item<T> array[MAXN];
    int32_t size = -1;
};


#endif //PRIORITYQUEUE_H
