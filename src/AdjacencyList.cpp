#include "AdjacencyList.h"

#include <iostream>

#include "Router.h"

template<typename T>
void Graph<T>::addNode(T node) {
    // adjList.insert(node);
}

template<typename T>
void Graph<T>::removeNode(T node) {
    // adjList.erase(node);
    // adjList.erase_if([node](auto &e) {
    //    std::cout << e << std::endl;
    // });
}

template<typename T>
void Graph<T>::addEdge(T u, T v, int weight) {
    // adjList.insert(u, std::tuple<T,int>(v,weight));
    // adjList.insert(v, std::tuple<T,int>(u,weight));

}

template<typename T>
void Graph<T>::removeEdge(int u, int v) {
    // adjList[u].erase(v);
    // adjList[v].erase(u);
}

template<typename T>
void Graph<T>::printGraph() {
    // adjList.visit_all([](auto &k) {
    //
    // });
}

template class Graph<Router>;
