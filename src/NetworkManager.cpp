#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    return NetworkManager::_instance;
}

void NetworkManager::addRouter(Router *router) {
    graph.addNode(router);
    ++router_count;
}

void NetworkManager::connect(Router *router1, Router *router2, uint16_t weight = 0) {
    if (weight == 0) {
        weight = router1->delay() + router2->delay();
    }
    graph.addEdge(router1, router2, weight);
}

NetworkManager *NetworkManager::_instance = new NetworkManager;


NetworkManager::NetworkManager() = default;

void NetworkManager::printGraph() {
    graph.printGraph();
}


void NetworkManager::resolveTaskTimer() {
    while (!timer_stop) {
        graph.visitAllNode([](Router* router) {
           //get current timestamp
        });
    }
}

void NetworkManager::stopTimer() {
    timer_stop.store(true,std::memory_order_release);
}
