#include <random>
#include <benchmark/benchmark.h>

#include "NetworkManager.h"
#include "Router.h"
#include "data_structure/PriorityQueue.h"

static void BM_SimpleRouterDijstraResolve(benchmark::State &state) {
    const auto router1 = std::make_shared<Router>("1");
    const auto router2 = std::make_shared<Router>("2");
    const auto router3 = std::make_shared<Router>("3");
    const auto router4 = std::make_shared<Router>("4");

    auto nm = NetworkManager::getInstance();
    nm->stopTimer();
    nm->addRouter(router1.get());
    nm->addRouter(router2.get());
    nm->addRouter(router3.get());
    nm->addRouter(router4.get());

    nm->connect(router1.get(), router2.get(), 3);
    nm->connect(router2.get(), router3.get(), 4);
    nm->connect(router1.get(), router3.get(), 2);
    nm->connect(router1.get(), router4.get(), 10);
    nm->connect(router3.get(), router4.get(), 1);

    for (auto _:state) {
        router1->resolve();
    }
}

BENCHMARK(BM_SimpleRouterDijstraResolve);

static void BM_1000RouterDijstraResolve(benchmark::State &state) {
    std::random_device rd_;
    std::mt19937 gen_(rd_());
    std::uniform_int_distribution<> distro_(0, 200);
    auto pg = PriorityQueue<Router*>();
    auto nm = NetworkManager::getInstance();
    nm->stopTimer();
    for (int i = 0; i < 1000; i++) {
        const auto delay = distro_(gen_);
        auto router = std::make_shared<Router>(std::to_string(i), delay);
        nm->addRouter(router.get());
        pg.enqueue(router.get(), delay);
    }
    Router* another_router_ = pg.pop();
    for (int i = 0; i < 1000; i++) {
        if (another_router_ != pg.top()) {
            nm->connect(another_router_, pg.top());
            another_router_ = pg.pop();
        }
    }
    for (auto _: state) {
        another_router_->resolve();
    }
}

BENCHMARK(BM_1000RouterDijstraResolve);

BENCHMARK_MAIN();
