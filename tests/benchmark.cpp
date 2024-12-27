#include <random>
#include <benchmark/benchmark.h>

#include "NetworkManager.h"
#include "Router.h"

static void BM_RouterDijkstraResolve(benchmark::State &state, int routers_edges_num) {
    std::random_device rd_;
    std::mt19937 gen_(rd_());
    std::uniform_int_distribution<> distro_(0, routers_edges_num - 1);

    Router *router_array[routers_edges_num];
    auto nm = NetworkManager::getInstance();
    nm->stopTimer();

    for (int i = 0; i < routers_edges_num; i++) {
        const auto router = new Router(std::to_string(i));
        nm->addRouter(router);
        router_array[i] = router;
    }
    uint32_t edges = 0;
    while (edges < routers_edges_num) {
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

static void BM_RouterDijkstraResolveWith_N_RouterAndEdges(benchmark::State &state) {
    BM_RouterDijkstraResolve(state, static_cast<int>(state.range(0)));
}

BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(100);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(500);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(1000);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(2000);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(5000);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(10000);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(20000);
BENCHMARK(BM_RouterDijkstraResolveWith_N_RouterAndEdges)->Arg(50000);

BENCHMARK_MAIN();
