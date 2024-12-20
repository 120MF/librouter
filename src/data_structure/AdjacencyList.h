#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "Hashmap.h"

template<typename T, typename HashFunc>
class Graph {
public:

    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, int weight);

    void removeEdge(T u, T v);

    void printGraph();

private:
    Hashmap<T, Hashmap<T, int, HashFunc>, HashFunc> adjList;
};


#endif //ADJACENCYLIST_H
