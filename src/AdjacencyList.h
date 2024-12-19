#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <atomic>
#include <unordered_map>

#include "Hashmap.h"

template<typename T>
class Graph {
public:
    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, int weight);

    void removeEdge(int u, int v);

    void printGraph();

private:
    std::atomic<Hashmap<T, Hashmap<T, int> > > adjList;
};


#endif //ADJACENCYLIST_H
