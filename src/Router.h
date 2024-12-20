#ifndef ROUTER_H
#define ROUTER_H

#include <cstdint>
#include <iostream>
#include <uuid_v4.h>

class Router {
public:
  explicit Router();

  friend bool operator==(const Router &lhs, const Router &rhs) {
    return lhs._uuid == rhs._uuid;
  }

  friend bool operator!=(const Router &lhs, const Router &rhs) {
    return !(lhs == rhs);
  }

  friend std::ostream &operator<<(std::ostream &os, const Router &obj) {
    return os << obj._uuid;
  }

private:
  UUIDv4::UUID _uuid;

public:
  [[nodiscard]] const UUIDv4::UUID &uuid() const {
    return _uuid;
  }
};

struct RouterHashCompute {
  uint32_t operator()(const Router &router) const {
    return std::hash<std::string>()(router.uuid().bytes()) % UINT32_MAX;
  }
};

#endif // !ROUTER_H
