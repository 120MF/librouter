#ifndef ROUTER_H
#define ROUTER_H

#include <cstdint>
#include <iostream>
#include <memory>

#include "NetworkManager.h"
#include "algorithm/DijkstraResolver.h"

class NetworkManager;

class Router {
public:
  Router();

  explicit Router(const std::string &name);

  explicit Router(uint16_t delay);

  Router(const std::string &name, uint16_t delay);

  void resolve();

private:
  std::string _uuid;
  std::string _name;
  uint16_t _delay{};
  DijkstraResolver<Router *, uint16_t> _dijkstra_resolver = DijkstraResolver<Router *, uint16_t>(this);

public:
  [[nodiscard]] const std::string &get_uuid() const {
    return _uuid;
  }

  [[nodiscard]] const std::string &get_name() const {
    return _name;
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
    return std::hash<std::string>()(router->get_uuid());
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
