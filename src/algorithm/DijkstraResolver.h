#ifndef DIJKSTRARESOLVER_H
#define DIJKSTRARESOLVER_H

#include "data_structure/Graph.h"
#include "data_structure/Stack.h"

template<typename T, typename WEIGHT_T>
struct node {
    T vertex;
    WEIGHT_T distance;
};

template<typename T, typename WEIGHT_T>
class DijkstraResolver {
public:
    explicit DijkstraResolver(T origin);


    void resolve(Graph<T, WEIGHT_T> *graph);

    WEIGHT_T getShortestWeight(T target);

    Stack<T> getShortestPath(T target);

private:
    T origin;
    Hashmap<T, T> predecessors;
    Hashmap<T, WEIGHT_T> dis;
};


#endif //DIJKSTRARESOLVER_H
