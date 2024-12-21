#include "NetworkManager.h"
#include "Router.h"
#include "data_structure/PriorityQueue.h"

int main() {
  auto nm = NetworkManager::getInstance();
  delete nm;

  return 0;
}
