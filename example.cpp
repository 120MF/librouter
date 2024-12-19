#include "NetworkManager.h"
#include "Router.h"

int main() {
  auto nm = NetworkManager::getInstance();
  nm->printGraph();
  return 0;
}
