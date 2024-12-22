#ifndef DIJKSTRARESOLVER_H
#define DIJKSTRARESOLVER_H
#include "data_structure/Graph.h"
#include "data_structure/PriorityQueue.h"
#include "utils/MaxValue.hpp"

template <typename T, typename WEIGHT_T>
struct node {
    T vertex;
    WEIGHT_T distance;
};

template <typename T, typename WEIGHT_T, typename T_HASHFUNC>
class DijkstraResolver {
public:
    explicit DijkstraResolver(T origin);


    PriorityQueue<node<T,WEIGHT_T>>* resolve(Graph<T,WEIGHT_T,T_HASHFUNC>* graph);
private:
    T origin;
    bool visited[MaxValue<WEIGHT_T>::value] = {};
    WEIGHT_T dis[MaxValue<WEIGHT_T>::value] = {};

    PriorityQueue<node<T,WEIGHT_T>> queue;
};



#endif //DIJKSTRARESOLVER_H
