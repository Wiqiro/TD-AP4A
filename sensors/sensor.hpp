#pragma once

#include <string>

template <typename T>
class Sensor {
   private:
    std::string name;

    virtual T aleaGenVal() = 0;

   public:
    Sensor() : name("unnamed_sensor") {}
    Sensor(const Sensor &sensor) : name(sensor.name) {}
    Sensor(std::string name) : name(name) {}
    ~Sensor() {}

    T sendData() { return aleaGenVal(); }

    std::string getName() { return name; }
};