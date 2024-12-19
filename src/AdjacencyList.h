#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "Hashmap.h"
#include "Router.h"
#include "List.h"

template<typename T>
class Graph {
public:
    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, int weight);

    void removeEdge(int u, int v);

    void printGraph();

private:
    Hashmap<T, Edge<T>, RouterHashCompute > adjList;
};


#endif //ADJACENCYLIST_H
