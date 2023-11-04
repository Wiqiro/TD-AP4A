#pragma once

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "sensors/sensor.hpp"

class Server {
   private:
    bool console_activation;
    bool logs_activation;
    std::filesystem::path logs_folder;

    /**
     * @brief Ecrit la valeur d'un capteur dans un fichier
     *
     * @tparam T le type de la valeur à écrire
     * @param file le fichier dans lequel écrire la valeur
     * @param data la valeur à écrire
     */
    template <typename T>
    void fileWrite(std::ofstream &file, T data) {
        // On récupère l'heure actuelle
        std::time_t time = std::time(nullptr);

        file << std::put_time(std::localtime(&time), "%X: ") << data
             << std::endl;
    }

    /**
     * @brief Ecrit la valeur d'un capteur dans la console
     *
     * @tparam T le type de la valeur à écrire
     * @param sensor_name le nom du capteur
     * @param data la valeur à écrire
     */
    template <typename T>
    void consoleWrite(std::string sensor_name, T data) {
        // On récupère l'heure actuelle
        std::time_t time = std::time(nullptr);

        std::cout << std::put_time(std::localtime(&time), "%X  ") << sensor_name
                  << ": " << data << std::endl;
    }

   public:
    /**
     * @brief Constructeur par défaut de la classe Server
     *
     */
    Server();

    /**
     * @brief Constructeur par recopie de la classe Server
     *
     * @param server le capteur à copier
     */
    Server(const Server &server);

    /**
     * @brief Constructeur de la classe Server
     *
     * @param logs_folder le chemin du dossier où les logs seront stockés
     * @param console_activation indique si les données sont affichées
     * @param logs_activation indique si les données sont loggées
     */
    Server(std::string logs_folder, bool console_activation,
           bool logs_activation);

    /**
     * @brief Destructeur de la classe Server
     */
    ~Server() = default;

    /**
     * @brief Opérateur d'affectation de la classe Server
     *
     * @param server le serveur à copier
     * @return Server& une référence au serveur copié
     */
    Server &operator=(const Server &server);

    /**
     * @brief Surcharge de l'opérateur << permettant de recevoir les données
     * d'un capteur
     *
     * @tparam T type de la valeur du capteur
     * @param server le serveur qui doit traiter la valeur
     * @param data les données du capteur (nom et valeur)
     */
    template <typename T>
    void operator<<(const std::tuple<std::string, T> &data) {
        // Simple appel à la fonction recieveDate avec les données du tuple
        this->recieveData(std::get<0>(data), std::get<1>(data));
    }

    /**
     * @brief Reçois les données d'un capteur pour les rediriger vers les
     * sorties
     *
     * @tparam T type de la valeur du capteur
     * @param sensor_name nom du capteur
     * @param data valeur du capteur
     */
    template <typename T>
    void recieveData(std::string sensor_name, T data) {
        if (console_activation) {
            consoleWrite(sensor_name, data);
        }

        if (logs_activation) {
            if (!std::filesystem::exists(logs_folder)) {
                // On créé le dossier des logs si il n'existe pas
                std::filesystem::create_directories(logs_folder);
            }
            // On ouvre le fichier du capteur à la fin
            std::ofstream sensor_file(logs_folder / sensor_name, std::ios::app);
            fileWrite(sensor_file, data);
            sensor_file.close();
        }
    }
};
