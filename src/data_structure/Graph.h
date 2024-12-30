#ifndef GRAPH_H
#define GRAPH_H

#include "ConcurrentHashmap.h"
#include "Hashmap.h"

/// An undirected, weighted graph restoring node and edges.
/// Concurrent supported since it use ConcurrentHashmap in the backend.
/// @tparam T anytype implemented std::hash<T>
/// @tparam WEIGHT_T type of edge weights
template<typename T, typename WEIGHT_T>
class Graph {
public:
    /// Get the Node that have the same hash in the params.
    /// Must pass a callback function to varify the Node and avoid from hash conflict
    /// @param hash the hash same as the target Node's.
    /// @param equal a callback function. Pass the Node found at the place, return whether the Node is the one you want to get.
    /// @return The Node that have the same hash in the params.
    T getNode(const uint32_t &hash, std::function<bool(T &)> equal);

    /// Add an isolated Node in the graph.
    /// @param node a Node of type T
    void addNode(T node);

    /// Remove a Node in the graph.
    /// @param node a Node of type T
    void removeNode(T node);

    /// Add an Edge with giving params.
    /// @param u a Node of type T
    /// @param v a Node of type T
    /// @param weight a WEIGHT_T type weight between two Nodes
    void addEdge(T u, T v, WEIGHT_T weight);

    /// Get the edge weight of two directly linked Nodes.
    /// @param u a Node of type T
    /// @param v a Node of type T
    /// @return the edge weight of two directly linked Nodes. 0 will be returned if no direct link found.
    WEIGHT_T getEdgeWeight(T &u, T &v);

    /// Remove the edge between two directly linked Nodes. Nothing will happen even though remove failed.
    /// @param u a Node of type T
    /// @param v a Node of type T
    void removeEdge(T u, T v);

    bool isLinked(T u, T v);

    /// Print the graph using std::cout stream
    void printGraph();

    /// Visit ALL the Node in the Graph, and execute func on each Node.
    /// @param func function to be executed on each Node
    void visitAllNode(std::function<void(T &)> func);

    /// Visit ALL the Node in the Graph, execute func on each Node.
    /// Stop when the flag become false.
    /// @param func function to be executed on each Node.
    /// @param flag reference to a boolean. Stop iterating when the flag become false.
    void visitAllNodeWhen(std::function<void(T &)> func, bool &flag);

    /// Visit ALL the Edge lined from one specific Node, execute func on each Edge.
    /// @param u a Node of type T
    /// @param func function to be executed on each Edge lined from the u
    void visitAllEdge(T &u, std::function<void(T, WEIGHT_T)> func);

private:
    ConcurrentHashmap<T, ConcurrentHashmap<T, WEIGHT_T> *> adjList = ConcurrentHashmap<
        T, ConcurrentHashmap<T, WEIGHT_T> *>();
};


#endif //GRAPH_H
