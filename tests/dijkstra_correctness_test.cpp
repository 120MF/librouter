#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "data_structure/Graph.h"
#include "algorithm/DijkstraResolver.h"

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> BoostGraph;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;

int main() {
    constexpr int num_nodes = 2000;
    constexpr int num_edges = 2000;

    std::vector<Edge> edge_array;
    std::vector<int> weights;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_nodes - 1);
    std::uniform_int_distribution<> weight_dis(1, 100);
    int cnt_edges = 0;
    while (cnt_edges < num_edges){
        int u = dis(gen);
        int v = dis(gen);
        if (u != v) {
            edge_array.emplace_back(u, v);
            weights.push_back(weight_dis(gen));
            ++cnt_edges;
        }
    }

    BoostGraph boost_graph(edge_array.begin(), edge_array.end(), weights.begin(), num_nodes);

    std::vector<Vertex> predecessors(num_nodes);
    std::vector<int> distances(num_nodes);
    Vertex start_vertex = 0;
    boost::dijkstra_shortest_paths(boost_graph, start_vertex,
        boost::predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, boost_graph))).
        distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, boost_graph))));

    constexpr int target_vertex = 1000;

    std::vector<int> boost_path;
    for (int v = target_vertex; v != start_vertex; v = predecessors[v]) {
        boost_path.push_back(v);
    }
    boost_path.push_back(start_vertex);
    std::ranges::reverse(boost_path);

    Graph<int, int> lr_graph;
    for (int i = 0; i < num_nodes; ++i) {
        lr_graph.addNode(i);
    }
    for (size_t i = 0; i < edge_array.size(); ++i) {
        lr_graph.addEdge(edge_array[i].first, edge_array[i].second, weights[i]);
    }

    DijkstraResolver<int, int> lr_dijkstra_resolver(start_vertex);
    lr_dijkstra_resolver.resolve(&lr_graph);
    Stack<int> lr_stack = lr_dijkstra_resolver.getShortestPath(target_vertex);

    std::vector<int> lr_path;
    while (!lr_stack.isEmpty()) {
        lr_path.push_back(lr_stack.pop());
    }
    assert(boost_path.size() == lr_path.size());
    while (!lr_path.empty()) {
        assert(lr_path.back() == boost_path.back());
        std::cout << boost_path.back() << std::endl;
        lr_path.pop_back();
        boost_path.pop_back();
    }
    return 0;
}