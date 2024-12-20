#include "Router.h"


Router::Router() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    const UUIDv4::UUID uuid = uuidGenerator.getUUID();
    this->_uuid = uuid;
    std::cout << "router " << _uuid << " initiliazed" << std::endl;
}
