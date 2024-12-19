#ifndef ROUTER_H
#define ROUTER_H

#include <cstdint>
#include <iostream>

class Router {
public:
  explicit Router();

  friend bool operator==(const Router &lhs, const Router &rhs) {
    return lhs._uuid == rhs._uuid;
  }

  friend bool operator!=(const Router &lhs, const Router &rhs) {
    return !(lhs == rhs);
  }

private:
  std::string _uuid;

public:
  [[nodiscard]] std::string uuid() const {
    return _uuid;
  }
};

struct RouterHashCompute {
  uint32_t operator()(const Router& router) const {
    return std::hash<std::string>()(router.uuid()) % UINT32_MAX;
  }
};

#endif // !ROUTER_H
