#include "NetworkManager.h"
#include "Router.h"
#include "data_structure/PriorityQueue.h"

int main() {
  auto nm = NetworkManager::getInstance();
  delete nm;

  auto router1 = new Router("A");
  auto router2 = new Router("B");
  auto router3 = new Router("C");
  PriorityQueue<Router*> pq;
  pq.enqueue(router1,10);
  pq.enqueue(router2,1);
  pq.enqueue(router3,10);
  std::cout << "1. " << *(pq.pop()) << std::endl << "2. " << *(pq.pop()) << std::endl << "3. " << *(pq.pop()) << std::endl;
  delete router1,router2,router3;
  return 0;
}
