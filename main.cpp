#include "server.h"

int main() {
    Server serv(true, true);
    serv.dataRcv("Uwu", 24);
    serv.dataRcv("Uwu", 24);
    serv.dataRcv("Uwu", 24);
    return 0;
}