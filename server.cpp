#include "server.h"

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

std::ostream &operator<<(std::ostream &os, std::string dataSensToString) {}




template void Server::fileWrite<int>(std::ofstream &file, int data);
template void Server::fileWrite<double>(std::ofstream &file, double data);
template void Server::fileWrite<bool>(std::ofstream &file, bool data);

template void Server::consoleWrite<int>(int data);
template void Server::consoleWrite<double>(double data);
template void Server::consoleWrite<bool>(bool data);

template void Server::dataRcv<int>(std::string sensorName, int data);
template void Server::dataRcv<double>(std::string sensorName, double data);
template void Server::dataRcv<bool>(std::string sensorName, bool data);