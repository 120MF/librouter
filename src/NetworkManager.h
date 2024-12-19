#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "AdjacencyList.h"
#include "Router.h"

class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager() = default;

    static NetworkManager *getInstance();

private:
    NetworkManager();

    Graph<Router> graph;

public:
    void printGraph();
};


#endif //NETWORKMANAGER_H
