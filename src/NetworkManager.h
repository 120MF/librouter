#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "data_structure/Graph.h"
#include "Router.h"
#include "../3rdparty/bs_thread_pool/include/BS_thread_pool.hpp"

class Router;

/// Class of
class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager();

    /// Get the only object of NetworkManager.
    /// @return the only object of NetworkManager
    static NetworkManager *getInstance();

    /// Add a Router into the NetworkManager.
    /// @param router Router to be added into NM
    void addRouter(Router *router);

    /// Remove a Router which may exist in the NetworkManager.
    /// @param router Router to be removed in the NM
    void removeRouter(Router *router);

    /// Return the edge weight between two directly linked Routers.
    /// @param router_s a router object
    /// @param router_v a router object
    /// @return the edge weight between two directly linked Routers. 0 will be returned if no direct link exist.
    uint32_t getLineDelay(Router *router_s, Router *router_v);

    /// Connect two Routers in the NetworkManager with edge weight calculated by their delays.
    /// @param router1 a router object
    /// @param router2 a router object
    void connect(Router *router1, Router *router2);

    /// Connect two Routers in the NetworkManager with giving edge weight.
    /// @param router1 a router object
    /// @param router2 a router object
    /// @param weight edge weight between the two routers
    void connect(Router *router1, Router *router2, uint16_t weight);

    /// Get the Router's graph and manually manipulate it.
    /// @return the router's graph
    Graph<Router *, uint16_t> *get_graph() { return &graph; }

    /// Stop running the Dijkstra resolve task
    void stopTimer();

private:
    NetworkManager();

    void resolveTaskTimer();

    static NetworkManager *_instance;

    Graph<Router *, uint16_t> graph;

    std::atomic<bool> timer_stop = false;

    std::atomic<uint16_t> router_count = 0;

    std::thread resolve_thread;

    BS::thread_pool<> pool;

public:
    /// Print the graph of all routers in the NetworkManager
    void printGraph();
};


#endif //NETWORKMANAGER_H
