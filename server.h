#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>

class Server {
private:
    std::string name;
    double data;

public:
/**
 * @brief Default constructor for Server
 */
    Server();

/**
 * @brief Copy constructor for Server
 * @param server: Server to copy
 */
    Server(const Server &server);

/**
 * @brief Construct a new Server object
 * 
 * @param name: Server's name
 * @param data: Server's data
 */
    Server(const std::string &name, double data);

    ~Server();

    Server &operator=(Server &server);

/**
 * @brief Write the server data inside a file
 * 
 * @param file: The file in which the server data should be written
 */
    void fileWrite(std::ofstream &file);

/**
 * @brief Outputs the server data in the console
 */
    void consoleWrite();

    const std::string &getName();
    const double &getData();

    friend std::ostream &operator<<(std::ostream &os, const Server &server);
};

