#include "DijkstraResolver.h"
#include "utils/MaxValue.hpp"
#include "Router.h"
#include "data_structure/PriorityQueue.h"

template<typename T, typename WEIGHT_T>
DijkstraResolver<T, WEIGHT_T>::DijkstraResolver(T origin): origin(origin) {
}

template<typename T, typename WEIGHT_T>
void DijkstraResolver<T, WEIGHT_T>::resolve(Graph<T, WEIGHT_T> *graph) {
    PriorityQueue<T> queue;
    Hashmap<T, bool> visited;

    graph->visitAllNode([this,&visited](T &u) {
        dis.set(u, MaxValue<WEIGHT_T>::value);
        visited.set(u, false);
    });
    dis.set(origin, 0);
    queue.enqueue(origin, 0);
    while (!queue.isEmpty()) {
        T u = queue.pop();
        if (visited.get(u)) continue;
        visited.set(u, true);
        graph->visitAllEdge(u, [this,&u,&queue](T v, WEIGHT_T w) {
            if (dis.get(v) > dis.get(u) + w) {
                dis.set(v, dis.get(u) + w);
                queue.enqueue(v, dis.get(v));
                predecessors.set(v, u);
            }
        });
    }
}

template<typename T, typename WEIGHT_T>
WEIGHT_T DijkstraResolver<T, WEIGHT_T>::getShortestWeight(T target) {
    try {
        return dis.get(target);
    } catch (const std::invalid_argument &) {
        return MaxValue<WEIGHT_T>::value;
    }
}

template<typename T, typename WEIGHT_T>
Stack<T> DijkstraResolver<T, WEIGHT_T>::getShortestPath(T target) {
    Stack<T> path;
    T prev = target;
    path.push(prev);
    try {
        do {
            prev = predecessors.get(prev);
            path.push(prev);
        } while (prev != origin);
        return path;
    } catch (const std::invalid_argument &) {
        return path;
    }
}

template class DijkstraResolver<Router *, uint16_t>;
template class DijkstraResolver<uint64_t, uint64_t>;
