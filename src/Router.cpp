#include "Router.h"
#include "uuid.h"

Router::Router() {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = " ";
    std::cout << "Unnamed router initiliazed" << std::endl;
}

Router::Router(const std::string& name) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = name;
    std::cout << "router " << name << " initiliazed" << std::endl;
}
