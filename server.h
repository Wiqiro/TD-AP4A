#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

class Server {
   private:
    std::string name;
    double temperature, humidity, sound, light;

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
    Server(const std::string &name, double temperature, double humidity,
           double sound, double light);

    ~Server();

    Server &operator=(const Server &server);

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

    friend std::ostream &operator<<(std::ostream &os, const Server &server);
};
