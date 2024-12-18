#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H


class NetworkManager {
public:
    NetworkManager(const NetworkManager &obj) = delete;

    NetworkManager &operator=(const NetworkManager &obj) = delete;

    ~NetworkManager() = default;

    static NetworkManager *getInstance();

private:
    NetworkManager() = default;
};


#endif //NETWORKMANAGER_H
