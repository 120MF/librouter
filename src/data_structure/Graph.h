#ifndef GRAPH_H
#define GRAPH_H

#include "Hashmap.h"

template<typename T, typename WEIGHT_T, typename HashFunc>
class Graph {
public:

    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, WEIGHT_T weight);

    void removeEdge(T u, T v);

    void printGraph();

private:
    Hashmap<T, Hashmap<T, WEIGHT_T, HashFunc>*, HashFunc> adjList;
};


#endif //GRAPH_H
