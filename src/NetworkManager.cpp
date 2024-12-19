#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    return NetworkManager::_instance;
}
NetworkManager* NetworkManager::_instance = new NetworkManager;

NetworkManager::NetworkManager(): graph() {
    auto router1 = Router();
    auto router2 = Router();
    auto router3 = Router();
    graph.addNode(router1);
    graph.addNode(router2);
    graph.addNode(router3);
    graph.addEdge(router1, router2, 3);
}

void NetworkManager::printGraph() {
    graph.printGraph();
}
