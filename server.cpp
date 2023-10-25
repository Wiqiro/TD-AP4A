#include "server.hpp"


Server::Server()
    : console_activation(true), logs_activation(true), logs_folder("logs") {}

Server::Server(const Server &server)
    : console_activation(server.console_activation),
      logs_activation(server.logs_activation),
      logs_folder(server.logs_folder) {}

Server::Server(std::string logs_folder, bool console_activation,
               bool logs_activation)
    : console_activation(console_activation),
      logs_activation(logs_activation),
      logs_folder(logs_folder) {}

Server::~Server() {}

Server &Server::operator=(const Server &server) {
    console_activation = server.console_activation;
    logs_activation = server.logs_activation;
    return *this;
}
