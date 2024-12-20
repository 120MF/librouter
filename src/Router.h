#ifndef ROUTER_H
#define ROUTER_H

#include <cstdint>
#include <iostream>
class Router {
public:
  Router();
  explicit Router(const std::string& name);

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
  std::string _uuid;
  std::string _name;

public:
  [[nodiscard]] const std::string &get_uuid() const {
    return _uuid;
  }
};

struct RouterHashCompute {
  uint32_t operator()(const Router &router) const {
    return std::hash<std::string>()(router.get_uuid()) % UINT16_MAX;
  }
};

#endif // !ROUTER_H
