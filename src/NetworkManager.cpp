#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    return NetworkManager::_instance;
}
NetworkManager* NetworkManager::_instance = new NetworkManager;

NetworkManager::NetworkManager(): graph() {
    auto router1 = std::make_shared<Router>("1");
    auto router2 = std::make_shared<Router>("2");
    auto router3 = std::make_shared<Router>("3");

    graph.addNode(router1);
    graph.addNode(router2);
    graph.addNode(router3);
    graph.addEdge(router1, router2, 3);
    graph.addEdge(router2, router3, 4);
    graph.addEdge(router1, router3, 2);

}

void NetworkManager::printGraph() {
    graph.printGraph();
}
