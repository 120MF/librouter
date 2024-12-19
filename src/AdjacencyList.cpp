#include "AdjacencyList.h"

#include <iostream>

template<typename T>
void Graph<T>::addNode(T node) {
    auto list = adjList.load();
    list.set(node, nullptr);
    adjList.store(list);
}

template<typename T>
void Graph<T>::removeNode(T node) {
    auto list = adjList.load();
    list.erase(node);

    for (auto &[key, neighbors]: list) {
        neighbors.erase(node);
    }
}

template<typename T>
void Graph<T>::addEdge(T u, T v, int weight) {
    adjList[u][v] = weight;
    adjList[v][u] = weight;
}

template<typename T>
void Graph<T>::removeEdge(int u, int v) {
    adjList[u].erase(v);
    adjList[v].erase(u);
}

template<typename T>
void Graph<T>::printGraph() {
    for (const auto &[node, neighbors]: adjList) {
        std::cout << node << ": ";
        for (const auto &[neighbor, weight]: neighbors) {
            std::cout << "(" << neighbor << ", " << weight << ") ";
        }
        std::cout << std::endl;
    }
}
