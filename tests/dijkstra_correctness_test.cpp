#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "data_structure/Graph.h"
#include "algorithm/DijkstraResolver.h"

#undef NDEBUG
#include <cassert>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<
    boost::edge_weight_t, uint64_t> > BoostGraph;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;
typedef std::pair<uint64_t, uint64_t> Edge;

int main() {
    constexpr uint64_t num_nodes = 1000;
    constexpr uint64_t num_edges = 3000;

    std::vector<Edge> edge_array;
    std::vector<uint64_t> weights;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_nodes - 1);
    std::uniform_int_distribution<> weight_dis(1, 100);
    uint64_t cnt_edges = 0;
    while (cnt_edges < num_edges) {
        uint64_t u = dis(gen);
        uint64_t v = dis(gen);
        if (u != v) {
            edge_array.emplace_back(u, v);
            weights.push_back(weight_dis(gen));
            ++cnt_edges;
        }
    }

    BoostGraph boost_graph(edge_array.begin(), edge_array.end(), weights.begin(), num_nodes);

    std::vector<Vertex> predecessors(num_nodes);
    std::vector<uint64_t> distances(num_nodes);
    Vertex start_vertex = 0;
    boost::dijkstra_shortest_paths(boost_graph, start_vertex,
                                   boost::predecessor_map(boost::make_iterator_property_map(
                                       predecessors.begin(), boost::get(boost::vertex_index, boost_graph))).
                                   distance_map(boost::make_iterator_property_map(
                                       distances.begin(), boost::get(boost::vertex_index, boost_graph))));

    uint64_t target_vertex = 200;
    while (distances[target_vertex] == std::numeric_limits<uint64_t>::max()) {
        ++target_vertex;
    }

    std::vector<uint64_t> boost_path;
    for (uint64_t v = target_vertex; v != start_vertex; v = predecessors[v]) {
        std::cout << v << std::endl;
        boost_path.push_back(v);
    }
    boost_path.push_back(start_vertex);
    std::ranges::reverse(boost_path);
    std::cout << "boost_path size: " << boost_path.size() << std::endl;
    std::cout << "boost_path sum: " << distances[target_vertex] << std::endl;

    Graph<uint64_t, uint64_t> lr_graph;
    for (uint64_t i = 0; i < num_nodes; ++i) {
        lr_graph.addNode(i);
    }
    for (uint64_t i = 0; i < num_edges; ++i) {
        lr_graph.addEdge(edge_array[i].first, edge_array[i].second, weights[i]);
    }

    DijkstraResolver<uint64_t, uint64_t> lr_dijkstra_resolver(start_vertex);
    lr_dijkstra_resolver.resolve(&lr_graph);
    Stack<uint64_t> lr_stack = lr_dijkstra_resolver.getShortestPath(target_vertex);

    std::vector<uint64_t> lr_path;
    while (!lr_stack.isEmpty()) {
        std::cout << "poped" << lr_stack.top() << std::endl;
        lr_path.push_back(lr_stack.pop());
    }
    std::cout << "librouter path size: " << lr_path.size() << std::endl;
    std::cout << "librouter path weight: " << lr_dijkstra_resolver.getShortestWeight(target_vertex) << std::endl;
    assert(boost_path.size() == lr_path.size());
    while (!lr_path.empty()) {
        assert(lr_path.back() == boost_path.back());
        lr_path.pop_back();
        boost_path.pop_back();
    }
    return 0;
}
