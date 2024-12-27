#include <random>
#include <benchmark/benchmark.h>

#include "NetworkManager.h"
#include "Router.h"

static void BM_RouterDijkstraResolve(benchmark::State &state) {
    std::random_device rd_;
    std::mt19937 gen_(rd_());
    std::uniform_int_distribution<> distro_(0, state.range() - 1);

    Router *router_array[state.range()];
    auto nm = NetworkManager::getInstance();
    nm->stopTimer();

    for (int i = 0; i < state.range(); i++) {
        const auto router = new Router(std::to_string(i));
        nm->addRouter(router);
        router_array[i] = router;
    }
    uint32_t edges = 0;
    while (edges < state.range()) {
        Router *router = router_array[distro_(gen_)];
        Router *another_router_ = router_array[distro_(gen_)];
        if (another_router_ != router) {
            ++edges;
            nm->connect(another_router_, router);
        }
    }
    Router *another_router_ = router_array[distro_(gen_)];
    for (auto _: state) {
        another_router_->resolve();
    }
    for (const Router *router: router_array) {
        delete router;
    }
}


BENCHMARK(BM_RouterDijkstraResolve)->Arg(100);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(500);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(1000);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(2000);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(5000);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(10000);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(20000);
BENCHMARK(BM_RouterDijkstraResolve)->Arg(50000);

static void BM_AddRouter(benchmark::State &state) {
    std::random_device rd_;
    std::mt19937 gen_(rd_());
    std::uniform_int_distribution<> distro_(0, 50000 - 1);
    Router *router_array[50000];
    auto nm = NetworkManager::getInstance();
    nm->stopTimer();
    for (int i = 0; i < 50000; i++) {
        const auto router = new Router(std::to_string(i));
        nm->addRouter(router);
        router_array[i] = router;
    }
    uint32_t edges = 0;
    while (edges < 50000) {
        Router *router = router_array[distro_(gen_)];
        Router *another_router_ = router_array[distro_(gen_)];
        if (another_router_ != router) {
            ++edges;
            nm->connect(another_router_, router);
        }
    }
    for (auto _: state) {
        const auto router = std::make_shared<Router>();
        nm->addRouter(router.get());
    }
    for (const Router *router: router_array) {
        delete router;
    }
}

BENCHMARK(BM_AddRouter);

static void BM_GraphEraseNode(benchmark::State &state) {
    std::random_device rd_;
    std::mt19937 gen_(rd_());
    std::uniform_int_distribution<> distro_(0, 50000 - 1);
    Graph<int, int> graph;
    for (int i = 0; i < 50000; i++) {
        graph.addNode(i);
    }
    uint32_t edges = 0;
    while (edges < 50000) {
        int node = distro_(gen_);
        int another_node = distro_(gen_);
        if (another_node != node) {
            ++edges;
            graph.addEdge(node, another_node, 10);
        }
    }
    for (auto _: state) {
        graph.removeNode(distro_(gen_));
    }
}

BENCHMARK(BM_GraphEraseNode);

BENCHMARK_MAIN();
