#include "DijkstraResolver.h"

#include <cstring>
#include <iostream>

template<typename T, typename WEIGHT_T>
DijkstraResolver<T, WEIGHT_T>::DijkstraResolver(T origin): origin(origin) {
}

template<typename T, typename WEIGHT_T>
PriorityQueue<node<T, WEIGHT_T> > *DijkstraResolver<T, WEIGHT_T>::resolve(Graph<T, WEIGHT_T> *graph) {
    memset(dis, MaxValue<WEIGHT_T>::value, sizeof(dis));
    memset(visited, 0, sizeof(visited));
    dis[origin] = 0;
    queue.enqueue({origin, 0});
    while (!queue.isEmpty()) {
        WEIGHT_T u = queue.pop();
        std::cout << u << std::endl;
        if (visited[u]) continue;
        visited[u] = true;
        graph->visitAllEdge(u, [this,u](T &v, WEIGHT_T &w) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                queue.enqueue({dis[v], v});
            }
        });
    }
    return &queue;
}
