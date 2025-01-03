#include "NetworkManager.h"
#include "Router.h"
#include "data_structure/Stack.h"

int main() {
  auto nm = NetworkManager::getInstance();
  auto router1 = new Router("1");
  auto router2 = new Router("2");
  auto router3 = new Router("3");
  auto router4 = new Router("4");
  auto router5 = new Router("5");

  nm->addRouter(router1);
  nm->addRouter(router2);
  nm->addRouter(router3);
  nm->addRouter(router4);
  nm->addRouter(router5);
  nm->connect(router1, router2, 3);
  nm->connect(router2, router3, 4);
  nm->connect(router1, router3, 2);
  nm->connect(router1, router4, 10);
  nm->connect(router3, router4, 1);

  nm->connect(router5, router1, 5);
  nm->connect(router5, router2, 10);

  std::cout << std::chrono::system_clock::now() << std::endl;
  nm->removeRouter(router5);
  std::cout << std::chrono::system_clock::now() << std::endl;

  nm->printGraph();

  std::cout << "------------" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  Stack<Router *> stack = router1->getShortestPath(router4);

  while (!stack.isEmpty()) {
    std::cout << stack.pop() << std::endl;
  }


  delete router1, router2, router3, router4, router5;

  return 0;
}
