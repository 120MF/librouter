#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>

class Router {
public:
  explicit Router(int id);

private:
  unsigned int _id;

public:
  [[nodiscard]] unsigned int id() const {
    return _id;
  }
};
#endif // !ROUTER_H
