#include <filesystem>
#include "server.hpp"



int main() {
    Server serv(true, true);
    serv.dataRcv("test", 24);
    serv.dataRcv("test", 24);
    serv.dataRcv("test", 24);
    return 0;
}