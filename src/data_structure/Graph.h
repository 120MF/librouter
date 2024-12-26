#ifndef GRAPH_H
#define GRAPH_H

#include "ConcurrentHashmap.h"
#include "Hashmap.h"

class Router;

template <typename T, typename WEIGHT_T>
class Graph
{
public:
    T getNode(const uint32_t& hash);

    void addNode(T node);

    void removeNode(T node);

    void addEdge(T u, T v, WEIGHT_T weight);

    WEIGHT_T getEdgeWeight(T& u, T& v);

    void removeEdge(T u, T v);

    void printGraph();

    void visitAllNode(std::function<void(T&)> func);
    void visitAllNodeWhen(std::function<void(T&)> func, bool& flag);

    void visitAllEdge(T& u, std::function<void(T, WEIGHT_T)> func);

private:
    ConcurrentHashmap<T, ConcurrentHashmap<T, WEIGHT_T>*> adjList = ConcurrentHashmap<
        T, ConcurrentHashmap<T, WEIGHT_T>*>();
};


#endif //GRAPH_H
