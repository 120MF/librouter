#ifndef ROUTER_H
#define ROUTER_H

#include <cstdint>
#include <future>
#include <iostream>
#include <memory>


#include "algorithm/DijkstraResolver.h"

class NetworkManager;

class Router {
public:
  /// Construct the Router by default.
  /// Router Delay will be randomly generate, while Router name will be set to " "
  Router();

  /// Construct the Router by giving name. Router Delay will be randomly generate.
  /// @param name Router's name
  explicit Router(const std::string &name);

  /// Construct the Router by giving delay. Router name will be set to " "
  /// @param delay Router's delay, mustn't be negative
  explicit Router(uint16_t delay);

  /// Construct the Router by giving name and delay.
  /// @param name Router's name
  /// @param delay Router's delay, mustn't be negative
  Router(const std::string &name, uint16_t delay);

  /// Run Dijkstra start from the Router
  void resolve();

  /// Get the shortest path from the router to the target router.
  /// It will get stuck when the resolve task is running.
  /// @param target the target router.
  /// @return a Stack containing the path. use Stack::pop() method to iterate it.
  Stack<Router *> getShortestPath(Router *target);

  std::chrono::time_point<std::chrono::system_clock> last_update_timestamp;
  std::future<void> have_updated;

private:
  std::string _uuid;
  std::string _name;
  uint16_t _delay{};
  uint32_t _hash;

private:
  DijkstraResolver<Router *, uint16_t> _dijkstra_resolver = DijkstraResolver<Router *, uint16_t>(this);

public:
  [[nodiscard]] const std::string &uuid() const {
    return _uuid;
  }

  [[nodiscard]] const std::string &name() const {
    return _name;
  }

  [[nodiscard]] uint16_t delay() const {
    return _delay;
  }

  [[nodiscard]] uint32_t hash() const {
    return _hash;
  }

public:
  friend bool operator==(const Router &lhs, const Router &rhs) {
    return lhs._uuid == rhs._uuid;
  }

  friend bool operator!=(const Router &lhs, const Router &rhs) {
    return !(lhs == rhs);
  }

  friend std::ostream &operator<<(std::ostream &os, const Router &obj) {
    return os << obj._name;
  }
};

template<>
struct std::hash<Router> {
  std::size_t operator()(const Router *router) const noexcept {
    return router->hash();
  }
};


inline std::ostream &operator<<(std::ostream &os, const Router *router) {
  if (router) {
    os << *router;
  } else {
    os << "null";
  }
  return os;
}


#endif // !ROUTER_H
