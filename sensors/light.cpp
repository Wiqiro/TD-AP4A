#include "light.hpp"

void LightSensor::aleaGenVal() { value = (rand() % 2 == 0); }

LightSensor::LightSensor() : Sensor(){};

LightSensor::LightSensor(const LightSensor& sensor) : Sensor(sensor) {}

LightSensor::LightSensor(std::string name, int interval)
    : Sensor(name, interval) {}

LightSensor::~LightSensor() {}

LightSensor& LightSensor::operator=(const LightSensor& sensor) {
    if (this != &sensor) {
        Sensor<bool>::operator=(sensor);
    }
    return *this;
}