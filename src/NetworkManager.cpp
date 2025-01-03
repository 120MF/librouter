#include "NetworkManager.h"
#include "Router.h"

NetworkManager *NetworkManager::getInstance() {
    return NetworkManager::_instance;
}

void NetworkManager::addRouter(Router *router) {
    graph.addNode(router);
    ++router_count;
}

void NetworkManager::removeRouter(Router *router) {
    graph.removeNode(router);
    --router_count;
}

uint32_t NetworkManager::getLineDelay(Router *router_s, Router *router_v) {
    return graph.getEdgeWeight(router_s, router_v);
}

void NetworkManager::connect(Router *router1, Router *router2) {
    auto weight = router1->delay() + router2->delay();
    graph.addEdge(router1, router2, weight);
}

void NetworkManager::connect(Router *router1, Router *router2, uint16_t weight = 0) {
    graph.addEdge(router1, router2, weight);
}

NetworkManager *NetworkManager::_instance = new NetworkManager;

NetworkManager::NetworkManager() {
    resolve_thread = std::thread(&NetworkManager::resolveTaskTimer, this);
};

NetworkManager::~NetworkManager() {
    stopTimer();
    resolve_thread.join();
}


void NetworkManager::printGraph() {
    graph.printGraph();
}


void NetworkManager::resolveTaskTimer() {
    while (!timer_stop) {
        if (router_count == 0) continue;
        auto now = std::chrono::system_clock::now();
        graph.visitAllNode([now, this](Router *router) {
            const auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - router->last_update_timestamp);
            if (duration.count() >= 2) {
                // If 2 or more seconds have elapsed
                // Update the timestamp in the router
                router->last_update_timestamp = now;
                // Submit resolve task and get a future
                router->have_updated = pool.submit_task([router]() { router->resolve(); });
            }
        });
    }
    // Push tasks every 1 second.
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void NetworkManager::stopTimer() {
    timer_stop.store(true, std::memory_order_release);
}
