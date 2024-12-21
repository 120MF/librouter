#include "AdjacencyList.h"

#include <iostream>

#include "Router.h"

template<typename T, typename HashFunc>
void Graph<T, HashFunc>::addNode(T node) {
    adjList.set(node, std::make_shared<Hashmap<T, int, HashFunc>>());
}

template<typename T, typename HashFunc>
void Graph<T, HashFunc>::removeNode(T node) {
    adjList.erase(node);
    auto func = [node](T &, std::shared_ptr<Hashmap<T, int, HashFunc>> &edges) {
        edges->erase(node);
    };
    adjList.visitAll(func);
}

template<typename T, typename HashFunc>
void Graph<T, HashFunc>::addEdge(T u, T v, int weight) {
    adjList.get(u)->set(v, weight);
    adjList.get(v)->set(u, weight);
}

template<typename T, typename HashFunc>
void Graph<T, HashFunc>::removeEdge(T u, T v) {
    adjList.get(u)->erase(v);
    adjList.get(v)->erase(u);
}

template<typename T, typename HashFunc>
void Graph<T, HashFunc>::printGraph() {
    adjList.visitAll([](T &node, std::shared_ptr<Hashmap<T, int, HashFunc>> &edge) {
        std::cout << node << std::endl;
        edge->visitAll([](T &key, int &value) {
            std::cout << key << " " << value << std::endl;
        });
        std::cout << std::endl;
    });
}

template class Graph<std::shared_ptr<Router>, RouterHashCompute>;
