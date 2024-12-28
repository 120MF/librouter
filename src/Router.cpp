#include "Router.h"
#include "uuid.h"
#include "utils/HashCompute.hpp"
#include "NetworkManager.h"

std::random_device rd_;
std::mt19937 gen_(rd_());
std::uniform_int_distribution<> distro_(0, 200);


Router::Router() {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_hash = std::hash<std::string>()(_uuid);
    this->_name = " ";
    _delay = distro_(gen_);
}

Router::Router(uint16_t delay) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_hash = std::hash<std::string>()(_uuid);
    this->_name = " ";
    _delay = delay;
}

Router::Router(const std::string &name) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_hash = std::hash<std::string>()(_uuid);
    this->_name = name;
    _delay = distro_(gen_);
}

Router::Router(const std::string &name, uint16_t delay) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_hash = std::hash<std::string>()(_uuid);
    this->_name = name;
    _delay = delay;
}

void Router::resolve() {
    const auto nm = NetworkManager::getInstance();
    const auto graph = nm->get_graph();
    _dijkstra_resolver.resolve(graph);
}

Stack<Router *> Router::getShortestPath(Router *target) {
    if (target == this) {
        Stack<Router *> s;
        s.push(target);
        return s;
    }

    // Waiting for the resolve task to finish
    have_updated.wait();

    return _dijkstra_resolver.getShortestPath(target);
}

uint32_t Router::getShortestWeight(Router *target) {
    return _dijkstra_resolver.getShortestWeight(target);
}

