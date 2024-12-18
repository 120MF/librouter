#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "AdjacencyList.h"

class Router;

class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager() = default;

    static NetworkManager *getInstance();

private:
    NetworkManager();
    static NetworkManager* _instance;

    Graph<Router> graph;

public:
    void printGraph();
};


#endif //NETWORKMANAGER_H
