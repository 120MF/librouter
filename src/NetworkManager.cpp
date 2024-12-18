#include "NetworkManager.h"

NetworkManager *NetworkManager::getInstance() {
    static NetworkManager nm;
    return &nm;
}
