#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "data_structure/Graph.h"
#include "Router.h"
#include "../3rdparty/bs_thread_pool/include/BS_thread_pool.hpp"

class Router;

class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager();

    static NetworkManager *getInstance();

    void addRouter(Router *router);
    void removeRouter(Router *router);
    uint32_t getLineDelay(Router *router_s, Router *router_v);

    void connect(Router *router1, Router *router2);
    void connect(Router *router1, Router *router2, uint16_t weight);

    Graph<Router *, uint16_t> *get_graph() { return &graph; }

    void resolveTaskTimer();

    void stopTimer();

private:
    NetworkManager();

    static NetworkManager *_instance;

    Graph<Router *, uint16_t> graph;

    std::atomic<bool> timer_stop = false;

    std::atomic<uint16_t> router_count = 0;

    std::thread resolve_thread;

    BS::thread_pool<> pool;

public:
    void printGraph();
};


#endif //NETWORKMANAGER_H
