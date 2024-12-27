#include <benchmark/benchmark.h>

#include "NetworkManager.h"
#include "Router.h"

// // Define another benchmark
// static void BM_StringCopy(benchmark::State &state) {
//     std::string x = "hello";
//     for (auto _: state)
//         std::string copy(x);
// }
//
// BENCHMARK(BM_StringCopy);

static void BM_RouterDijstraResolve(benchmark::State &state) {
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

BENCHMARK(BM_RouterDijstraResolve);

BENCHMARK_MAIN();
