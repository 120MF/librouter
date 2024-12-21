#include "DijkstraResolver.h"

#include <cstring>

template <typename T, typename WEIGHT_T, typename T_HASHFUNC>
DijkstraResolver<T, WEIGHT_T, T_HASHFUNC>::DijkstraResolver(T origin, Graph<T,WEIGHT_T,T_HASHFUNC>* graph): origin(origin), graph(graph) {
}

template <typename T, typename WEIGHT_T, typename T_HASHFUNC>
PriorityQueue<node<T,WEIGHT_T>> * DijkstraResolver<T,WEIGHT_T,T_HASHFUNC>::resolve() {
    memset(dis, MaxValue<WEIGHT_T>::value, sizeof(dis));
    memset(visited, 0, sizeof(visited));
    dis[origin] = 0;
    queue.enqueue({origin, 0});
    while (!queue.isEmpty()) {
        WEIGHT_T u = queue.pop();
        if (visited[u]) continue;
        visited[u] = true;

    }
}
