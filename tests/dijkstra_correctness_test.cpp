#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "data_structure/Graph.h"
#include "algorithm/DijkstraResolver.h"

#undef NDEBUG
#include <cassert>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<
    boost::edge_weight_t, uint64_t> > BoostGraph;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;
typedef std::pair<uint64_t, uint64_t> Edge;

std::set<Edge> edge_set;

int main() {
    constexpr uint64_t num_nodes = 1000;
    constexpr uint64_t num_edges = 2000;

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
            Edge edge = std::make_pair(u, v);
            Edge reverse_edge = std::make_pair(v, u);
            if (!edge_set.contains(edge) && !edge_set.contains(reverse_edge)) {
                edge_array.emplace_back(edge);
                weights.push_back(weight_dis(gen));
                edge_set.insert(edge);
                edge_set.insert(reverse_edge);
                ++cnt_edges;
            }
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

    uint64_t target_vertex = num_nodes / 4;
    while (distances[target_vertex] == std::numeric_limits<uint64_t>::max()) {
        ++target_vertex;
    }

    std::vector<uint64_t> boost_path;
    for (uint64_t v = target_vertex; v != start_vertex; v = predecessors[v]) {
        boost_path.push_back(v);
    }
    boost_path.push_back(start_vertex);
    std::ranges::reverse(boost_path);

    // Save edges and weights to a file
    // std::ofstream edge_file("edges_weights.txt");
    // for (size_t i = 0; i < edge_array.size(); ++i) {
    //     edge_file << edge_array[i].first << " " << edge_array[i].second << " " << weights[i] << "\n";
    // }
    // edge_file.close();
    //
    // // Save shortest path to a file
    // std::ofstream path_file("shortest_path.txt");
    // for (const auto &vertex: boost_path) {
    //     path_file << vertex << " ";
    // }
    // path_file << "\n";
    // path_file.close();

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
        lr_path.push_back(lr_stack.pop());
    }
    assert(boost_path.size() == lr_path.size());
    std::cout << "Length Correct" << std::endl;
    assert(distances[target_vertex] == lr_dijkstra_resolver.getShortestWeight(target_vertex));
    std::cout << "Distance Correct" << std::endl;
    while (!lr_path.empty()) {
        assert(lr_path.back() == boost_path.back());
        lr_path.pop_back();
        boost_path.pop_back();
    }
    std::cout << "Path Correct" << std::endl;
    return 0;
}
