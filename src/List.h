#ifndef EDGELIST_H
#define EDGELIST_H

template<typename T>
struct Edge {
    T to_vex;
    int weight;
};

template<typename T>
struct Node {
    T data;
    Node *next;
};

template<typename T>
class List {
public:
    List();

    ~List();

    void addNode(const T &node);

    void removeNode(const T &node);

    void clear();

    Node<T> *head;
};


#endif //EDGELIST_H
