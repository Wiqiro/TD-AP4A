#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
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
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        file << std::put_time(std::localtime(&in_time_t), "%X: ") << data
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
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::cout << std::put_time(std::localtime(&in_time_t), "%X  ")
                  << sensor_name << ": " << data << std::endl;
    }

   public:
    Server();
    Server(const Server &server);
    Server(std::string logs_folder, bool console_activation, bool logs_activation);
    ~Server();

    Server &operator=(const Server &server);
     
    /**
     * @brief Reçois les données d'un capteur pour les rediriger vers les sorties
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
                std::filesystem::create_directories(logs_folder);
            }
            std::ofstream sensor_file(logs_folder / sensor_name, std::ios::app);
            fileWrite(sensor_file, data);
            sensor_file.close();
        }
    }
};
