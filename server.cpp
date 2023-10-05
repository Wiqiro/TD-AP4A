#include "server.h"

Server::Server()
    : name("unnamed-server"), temperature(0), humidity(0), sound(0), light(0) {}

Server::Server(const Server& server)
    : name(server.name),
      temperature(server.temperature),
      humidity(server.humidity),
      sound(server.sound),
      light(server.light) {}

Server::Server(const std::string& name, double temperature, double humidity,
               double sound, double light)
    : name(name),
      temperature(temperature),
      humidity(humidity),
      sound(sound),
      light(light) {}

Server::~Server() {}

Server& Server::operator=(const Server& server) {
    name = server.name;
    temperature = server.temperature;
    humidity = server.humidity;
    sound = server.sound;
    light = server.light;
    return *this;
}

void Server::fileWrite(std::ofstream& file) {
    if (file.is_open()) {
        file << "Server name: " << name << std::endl;
        file << "Temperature: " << temperature << std::endl;
        file << "Humidity: " << humidity << std::endl;
        file << "Sound: " << sound << std::endl;
        file << "Light: " << light << std::endl;
    }
}

void Server::consoleWrite() {
    std::cout << "Server name: " << name << std::endl;
    std::cout << "Temperature: " << temperature << std::endl;
    std::cout << "Humidity: " << humidity << std::endl;
    std::cout << "Sound: " << sound << std::endl;
    std::cout << "Light: " << light << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "Server name: " << server.name << std::endl;
    os << "Temperature: " << server.temperature << std::endl;
    os << "Humidity: " << server.humidity << std::endl;
    os << "Sound: " << server.sound << std::endl;
    os << "Light: " << server.light << std::endl;
    return os;
}
