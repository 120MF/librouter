#include "Graph.h"

#include <iostream>
#include <utility>

#include "Router.h"


template<typename T, typename WEIGHT_T>
T Graph<T, WEIGHT_T>::getNode(const uint32_t &hash, std::function<bool(T &)> equal) {
    return adjList.getKey(hash, equal);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::addNode(T node) {
    adjList.set(node, new ConcurrentHashmap<T, WEIGHT_T>);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::removeNode(T node) {
    try {
        adjList.erase(node);
        auto func = [node](T, ConcurrentHashmap<T, WEIGHT_T> *edges) {
            edges->erase(node);
        };
        adjList.visitAll(func);
    } catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::addEdge(T u, T v, WEIGHT_T weight) {
    adjList.get(u)->set(v, weight);
    adjList.get(v)->set(u, weight);
}

template<typename T, typename WEIGHT_T>
WEIGHT_T Graph<T, WEIGHT_T>::getEdgeWeight(T &u, T &v) {
    try {
        return adjList.get(u)->get(v);
    } catch (const std::invalid_argument) {
        return 0;
    }
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::removeEdge(T u, T v) {
    adjList.get(u)->erase(v);
    adjList.get(v)->erase(u);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::printGraph() {
    adjList.visitAll([](T node, ConcurrentHashmap<T, WEIGHT_T> *edge) {
        std::cout << node << std::endl;
        edge->visitAll([](T key, WEIGHT_T value) {
            std::cout << key << " " << value << std::endl;
        });
        std::cout << std::endl;
    });
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::visitAllNode(std::function<void(T &)> func) {
    adjList.visitAll([func](T u, auto) {
        func(u);
    });
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::visitAllNodeWhen(std::function<void(T &)> func, bool &flag) {
    adjList.visitAllWhen([func](T u, auto) {
        func(u);
    }, flag);
}

template<typename T, typename WEIGHT_T>
void Graph<T, WEIGHT_T>::visitAllEdge(T &u, std::function<void(T, WEIGHT_T)> func) {
    auto edges = adjList.get(u);
    edges->visitAll(std::move(func));
}

template class Graph<Router *, uint16_t>;
template class Graph<int, int>;
