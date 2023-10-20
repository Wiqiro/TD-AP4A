#pragma once

#include <string>

class Sensor {
   private:
    std::string name;
    
    int aleaGenVal();

   public:
    Sensor();
    Sensor(const Sensor &sensor);
    Sensor(std::string name);
    ~Sensor();

    int sendData();
    std::string getName();
};