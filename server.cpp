#include "server.h"

Server::Server() {
    name = "unnamed-server";
}

Server::Server(const Server& server) {
    data = server.data;
}

Server::Server(const std::string &name, double data) {
    this->name = name;
    this->data = data;
}

Server::~Server() {}

Server& Server::operator=(Server& server) {
    return server;
}



void Server::fileWrite(std::ofstream &file) {
    if (file.is_open()) {
        file << data << std::endl;
    }
}

void Server::consoleWrite() {
    std::cout << data;
}

const std::string& Server::getName() {
    return name;
}

const double& Server::getData() {
    return data;
}

std::ostream &operator<<(std::ostream &os, const Server &server) {
    os << "Name: " << server.name << "  Data: " << server.data << "";
    return os;
}
