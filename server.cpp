#include "server.hpp"

/**
 * @brief Constructeur par défaut de la classe Server
 *
 */
Server::Server()
    : console_activation(true), logs_activation(true), logs_folder("logs") {}

/**
 * @brief Constructeur par recopie de la classe Server
 *
 * @param server le capteur à copier
 */
Server::Server(const Server &server)
    : console_activation(server.console_activation),
      logs_activation(server.logs_activation),
      logs_folder(server.logs_folder) {}

/**
 * @brief Constructeur de la classe Server
 *
 * @param logs_folder le chemin du dossier où les logs seront stockés
 * @param console_activation indique si les données sont affichées
 * @param logs_activation indique si les données sont loggées
 */
Server::Server(std::string logs_folder, bool console_activation,
               bool logs_activation)
    : console_activation(console_activation),
      logs_activation(logs_activation),
      logs_folder(logs_folder) {}

/**
 * @brief Opérateur d'affectation de la classe Server
 *
 * @param server le serveur à copier
 * @return Server& une référence au serveur copié
 */
Server &Server::operator=(const Server &server) {
    console_activation = server.console_activation;
    logs_activation = server.logs_activation;
    logs_folder = server.logs_folder;
    return *this;
}