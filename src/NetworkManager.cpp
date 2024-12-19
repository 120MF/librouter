#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    static NetworkManager nm;
    return &nm;
}

NetworkManager::NetworkManager(): graph() {
    auto router1 = Router(1);
    auto router2 = Router(2);
    auto router3 = Router(3);
    graph.addNode(router1);
    graph.addNode(router2);
    graph.addNode(router3);
    graph.addEdge(router1, router2, 3);
}

void NetworkManager::printGraph() {
    graph.printGraph();
}
