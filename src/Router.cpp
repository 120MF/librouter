#include "Router.h"
#include "uuid.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distro(0, 200);

Router::Router() {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = " ";
    _delay = distro(gen);
    std::cout << "Unnamed router initiliazed" << std::endl;
}

Router::Router(uint16_t delay) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = " ";
    _delay = delay;
    std::cout << "Unnamed router initiliazed" << std::endl;
}

Router::Router(const std::string& name) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = name;
    _delay = distro(gen);
    std::cout << "router " << name << " initiliazed" << std::endl;
}

Router::Router(const std::string &name, uint16_t delay) {
    uuids::uuid const id = uuids::uuid_system_generator{}();
    this->_uuid = uuids::to_string(id);
    this->_name = name;
    _delay = delay;
    std::cout << "router " << name << " initiliazed" << std::endl;
}
