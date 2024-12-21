#include "Graph.h"

#include <iostream>

#include "Router.h"

template<typename T, typename WEIGHT_T, typename HashFunc>
void Graph<T, WEIGHT_T, HashFunc>::addNode(T node) {
    adjList.set(node, new Hashmap<T, WEIGHT_T, HashFunc>);
}

template<typename T, typename WEIGHT_T, typename HashFunc>
void Graph<T, WEIGHT_T, HashFunc>::removeNode(T node) {
    adjList.erase(node);
    auto func = [node](T &, Hashmap<T, WEIGHT_T, HashFunc>* edges) {
        edges->erase(node);
    };
    adjList.visitAll(func);
}

template<typename T, typename WEIGHT_T, typename HashFunc>
void Graph<T, WEIGHT_T, HashFunc>::addEdge(T u, T v, WEIGHT_T weight) {
    adjList.get(u)->set(v, weight);
    adjList.get(v)->set(u, weight);
}

template<typename T, typename WEIGHT_T, typename HashFunc>
void Graph<T, WEIGHT_T, HashFunc>::removeEdge(T u, T v) {
    adjList.get(u)->erase(v);
    adjList.get(v)->erase(u);
}

template<typename T, typename WEIGHT_T, typename HashFunc>
void Graph<T, WEIGHT_T, HashFunc>::printGraph() {
    adjList.visitAll([](T &node, Hashmap<T, WEIGHT_T, HashFunc> *edge) {
        std::cout << node << std::endl;
        edge->visitAll([](T &key, WEIGHT_T &value) {
            std::cout << key << " " << value << std::endl;
        });
        std::cout << std::endl;
    });
}

template class Graph<Router*, uint16_t, RouterHashCompute>;
