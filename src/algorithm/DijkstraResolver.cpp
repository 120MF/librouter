#include "DijkstraResolver.h"

#include <iostream>
#include "utils/MaxValue.hpp"
#include "Router.h"

template<typename T, typename WEIGHT_T>
DijkstraResolver<T, WEIGHT_T>::DijkstraResolver(T origin): origin(origin) {
}

template<typename T, typename WEIGHT_T>
PriorityQueue<T> *DijkstraResolver<T, WEIGHT_T>::resolve(Graph<T, WEIGHT_T> *graph) {
    graph->visitAllNode([this](T &u) {
        dis.set(u, MaxValue<WEIGHT_T>::value);
        visited.set(u, false);
    });
    dis.set(origin, 0);
    queue.enqueue(origin, 0);
    while (!queue.isEmpty()) {
        T u = queue.pop();
        std::cout << u << std::endl;
        if (visited.get(u)) continue;
        visited.set(u, true);
        graph->visitAllEdge(u, [this,u](T &v, WEIGHT_T &w) {
            if (dis.get(v) > dis.get(u) + w) {
                dis.set(v, dis.get(u) + w);
                queue.enqueue(v, dis.get(v));
            }
        });
    }
    return &queue;
}

template class DijkstraResolver<Router *, uint16_t>;
