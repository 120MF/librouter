#ifndef DIJKSTRARESOLVER_H
#define DIJKSTRARESOLVER_H

#include "data_structure/Graph.h"
#include "data_structure/Stack.h"

/// A single source shortest path Graph resolver using Dijkstra algorithm.
/// @tparam T type of node in the Graph
/// @tparam WEIGHT_T type of weight of edges in the Graph
template<typename T, typename WEIGHT_T>
class DijkstraResolver {
public:
    /// Construct the resolver by giving origin
    /// @param origin the start node of Dijkstra
    explicit DijkstraResolver(T origin);

    /// Resolve the giving graph.
    /// @param graph a non-negative weight Graph
    void resolve(Graph<T, WEIGHT_T> *graph);

    /// Return the shortest path's edge weight sum from resolver's origin Node to the giving target Node.
    /// @param target target Node
    /// @return weight sum of type WEIGHT_T
    WEIGHT_T getShortestWeight(T target);

    /// Return the shortest path from resolver's origin Node to the giving target Node.
    /// @param target target Node
    /// @return a Stack containing the shortest path
    Stack<T> getShortestPath(T target);

private:
    T origin;
    Hashmap<T, T> predecessors;
    Hashmap<T, WEIGHT_T> dis;
};

#endif //DIJKSTRARESOLVER_H
