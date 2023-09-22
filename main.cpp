#include "server.h"

int main() {
    Server serv("Hervé", 12.2);
    std::cout << serv << std::endl;
    std::ofstream test_file("test");
    serv.fileWrite(test_file);
    
    return 0;
}