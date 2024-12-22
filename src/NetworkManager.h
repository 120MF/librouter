#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "data_structure/Graph.h"
#include "Router.h"

class Router;

class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager() = default;

    static NetworkManager *getInstance();

    void addRouter(Router *router);

    void connect(Router *router1, Router *router2, uint16_t weight);

    Graph<Router *, uint16_t> *get_graph() { return &graph; }

private:
    NetworkManager();

    static NetworkManager *_instance;

    Graph<Router *, uint16_t> graph;

public:
    void printGraph();
};


#endif //NETWORKMANAGER_H
