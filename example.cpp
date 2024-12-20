#include "NetworkManager.h"
#include "Router.h"

int main() {
  auto nm = NetworkManager::getInstance();
  nm->printGraph();
  delete nm;
  return 0;
}
