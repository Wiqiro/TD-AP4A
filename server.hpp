#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "sensors/sensor.hpp"

class Server {
   private:
    bool consolActivation;
    bool logActivation;

    template <typename T>
    void fileWrite(std::ofstream &file, T data) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        file << std::put_time(std::localtime(&in_time_t), "%X  ") << data
             << std::endl;
    }

    template <typename T>
    void consoleWrite(T data) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::cout << std::put_time(std::localtime(&in_time_t), "%X  ") << data
                  << std::endl;
    }

   public:
    Server();
    Server(const Server &server);
    Server(bool consolActivation, bool logActivation);

    ~Server();

    Server &operator=(const Server &server);
    friend std::ostream &operator<<(std::ostream &os, int &data);

    template <typename T>
    void dataRcv(std::string sensorName, T data) {
        std::ofstream sensorFile(sensorName, std::ios::app);
        fileWrite(sensorFile, data);
        consoleWrite(data);
        sensorFile.close();
    }
};
