#include "Router.h"
#include "uuid_v4.h"
UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;


Router::Router() {
    const UUIDv4::UUID uuid = uuidGenerator.getUUID();
    this->_uuid = uuid.bytes();
    std::cout << "router "<< _uuid << " initiliazed" << std::endl;
}
