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
  Router();

  explicit Router(const std::string &name);

  explicit Router(uint16_t delay);

  Router(const std::string &name, uint16_t delay);

  void resolve();

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
  [[nodiscard]] const std::string &get_uuid() const {
    return _uuid;
  }

  [[nodiscard]] const std::string &get_name() const {
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
