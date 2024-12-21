#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    return NetworkManager::_instance;
}
NetworkManager* NetworkManager::_instance = new NetworkManager;



NetworkManager::NetworkManager() {
    auto router1 = new Router("1");
    auto router2 = new Router("2");
    auto router3 = new Router("3");

    graph.addNode(router1);
    graph.addNode(router2);
    graph.addNode(router3);
    graph.addEdge(router1, router2, 3);
    graph.addEdge(router2, router3, 4);
    graph.addEdge(router1, router3, 2);

    printGraph();
    graph.removeEdge(router1,router2);
    printGraph();

    delete router1,router2,router3;

}

void NetworkManager::printGraph() {
    graph.printGraph();
}
