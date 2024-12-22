#ifndef GRAPH_H
#define GRAPH_H

#include "Hashmap.h"

class Router;

uint32_t RouterHashCompute(const Router *router);

template<typename T, typename WEIGHT_T>
class Graph {
public:
    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, WEIGHT_T weight);

    void removeEdge(T u, T v);

    void printGraph();

    void visitAllEdge(T u, std::function<void(T &, WEIGHT_T &)> func);

private:
    Hashmap<T, Hashmap<T, WEIGHT_T> *> adjList = Hashmap<T, Hashmap<T, WEIGHT_T> *>();
};


#endif //GRAPH_H
