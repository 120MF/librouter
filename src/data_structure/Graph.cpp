#include "Graph.h"

#include <iostream>
#include <utility>

#include "Router.h"

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::addNode(T node) {
    adjList.set(node, new Hashmap<T, WEIGHT_T>);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::removeNode(T node) {
    adjList.erase(node);
    auto func = [node](T &, Hashmap<T, WEIGHT_T> *edges) {
        edges->erase(node);
    };
    adjList.visitAll(func);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::addEdge(T u, T v, WEIGHT_T weight) {
    adjList.get(u)->set(v, weight);
    adjList.get(v)->set(u, weight);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::removeEdge(T u, T v) {
    adjList.get(u)->erase(v);
    adjList.get(v)->erase(u);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::printGraph() {
    adjList.visitAll([](T &node, Hashmap<T, WEIGHT_T> *edge) {
        std::cout << node << std::endl;
        edge->visitAll([](T &key, WEIGHT_T &value) {
            std::cout << key << " " << value << std::endl;
        });
        std::cout << std::endl;
    });
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::visitAllEdge(T u, std::function<void(T &, WEIGHT_T &)> func) {
    auto edges = adjList.get(u);
    edges->visitAll(std::move(func));
}

template class Graph<Router *, uint16_t>;
