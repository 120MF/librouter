#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
#include "data_structure/Graph.h"
#include "algorithm/DijkstraResolver.h"

// Define the graph using Boost
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> BoostGraph;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;

int main() {
    // Generate nodes and edges
    const int num_nodes = 5;
    Edge edge_array[] = { Edge(0, 1), Edge(0, 2), Edge(1, 2), Edge(1, 3), Edge(2, 3), Edge(3, 4) };
    int weights[] = { 10, 3, 1, 2, 4, 2 };
    const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

    // Create Boost graph
    BoostGraph boost_graph(edge_array, edge_array + num_edges, weights, num_nodes);

    // Calculate the shortest path using Boost's Dijkstra
    std::vector<Vertex> predecessors(num_nodes);
    std::vector<int> distances(num_nodes);
    Vertex start_vertex = 0;
    boost::dijkstra_shortest_paths(boost_graph, start_vertex,
        boost::predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, boost_graph))).
        distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, boost_graph))));

    // Print Boost's Dijkstra results
    std::cout << "Boost Dijkstra results:" << std::endl;
    for (int i = 0; i < num_nodes; ++i) {
        std::cout << "Distance to node " << i << " is " << distances[i] << std::endl;
    }

    // Function to print the shortest path from start_vertex to target_vertex
    auto print_path = [&](int target_vertex) {
        std::vector<int> path;
        for (int v = target_vertex; v != start_vertex; v = predecessors[v]) {
            path.push_back(v);
        }
        path.push_back(start_vertex);
        std::reverse(path.begin(), path.end());
        std::cout << "Path: ";
        for (int v : path) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    };

    // Print the shortest path to node 4
    print_path(4);

    // Create your graph
    Graph<int, int> my_graph;
    for (int i = 0; i < num_nodes; ++i) {
        my_graph.addNode(i);
    }
    for (int i = 0; i < num_edges; ++i) {
        my_graph.addEdge(edge_array[i].first, edge_array[i].second, weights[i]);
    }

    // Calculate shortest path using your Dijkstra resolver
    DijkstraResolver<int, int> my_dijkstra_resolver(start_vertex);
    my_dijkstra_resolver.resolve(&my_graph);
    Stack<int> my_stack = my_dijkstra_resolver.getShortestPath(4); // Assuming target is node 4

    // Print your Dijkstra results
    std::cout << "My Dijkstra results:" << std::endl;
    std::vector<int> my_path;
    while (!my_stack.isEmpty()) {
        my_path.push_back(my_stack.pop());
    }
    std::reverse(my_path.begin(), my_path.end());
    for (int node : my_path) {
        std::cout << "Node: " << node << std::endl;
    }

    return 0;
}