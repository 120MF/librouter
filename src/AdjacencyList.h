#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <atomic>

constexpr unsigned int MAX_VERTEX = 0xFFFFFFFF;

template<typename T>
struct VertexNode {
    T data;
    VertexNode *next;
};

struct ArcNode {
    int adjvex;
    ArcNode *next;
    int w;
};

template<typename T>
struct Graph {
    std::atomic<VertexNode<T> > vertices[MAX_VERTEX];
    int vex_count;
    int arc_num;
};

#endif //ADJACENCYLIST_H
