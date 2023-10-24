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

    template <typename T>
    void fileWrite(std::ofstream &file, T data) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        file << std::put_time(std::localtime(&in_time_t), "%X: ") << data
             << std::endl;
    }

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
    /*  friend std::ostream &operator<<(std::ostream &os, int &data); */

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
