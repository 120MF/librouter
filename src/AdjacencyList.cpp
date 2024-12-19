#include "AdjacencyList.h"

#include <iostream>

#include "Router.h"

template<typename T>
void Graph<T>::addNode(T node) {
    // adjList.set(node);
}

template<typename T>
void Graph<T>::removeNode(T node) {
    adjList.erase(node);
    auto func = [node](const List<Router>& edges) {
        const Node<Router>* list_head = edges.head;
        do {
            // if (list_head->next)
        } while (list_head != nullptr);
    };
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
