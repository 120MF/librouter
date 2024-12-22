#ifndef DIJKSTRARESOLVER_H
#define DIJKSTRARESOLVER_H
#include "data_structure/Graph.h"
#include "data_structure/PriorityQueue.h"

template<typename T, typename WEIGHT_T>
struct node {
    T vertex;
    WEIGHT_T distance;
};

template<typename T, typename WEIGHT_T>
class DijkstraResolver {
public:
    explicit DijkstraResolver(T origin);


    PriorityQueue<T> *resolve(Graph<T, WEIGHT_T> *graph);

private:
    T origin;
    Hashmap<T, bool> visited;
    Hashmap<T, WEIGHT_T> dis;

    PriorityQueue<T> queue;
};


#endif //DIJKSTRARESOLVER_H
