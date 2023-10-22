#include "server.hpp"

Server::Server() {
    consolActivation = 0;
    logActivation = 0;
}

Server::Server(const Server &server)
    : consolActivation(server.consolActivation),
      logActivation(server.logActivation) {}

Server::Server(bool consolActivation, bool logActivation)
    : consolActivation(consolActivation), logActivation(logActivation) {}

Server::~Server() {}

Server &Server::operator=(const Server &server) {
    consolActivation = server.consolActivation;
    logActivation = server.logActivation;
    return *this;
}

std::ostream &operator<<(std::ostream &os, int dataSens) {}




template void Server::fileWrite<int>(std::ofstream &file, int data);
template void Server::fileWrite<float>(std::ofstream &file, float data);
template void Server::fileWrite<bool>(std::ofstream &file, bool data);

template void Server::consoleWrite<int>(int data);
template void Server::consoleWrite<float>(float data);
template void Server::consoleWrite<bool>(bool data);

template void Server::dataRcv<int>(std::string sensorName, int data);
template void Server::dataRcv<float>(std::string sensorName, float data);
template void Server::dataRcv<bool>(std::string sensorName, bool data);