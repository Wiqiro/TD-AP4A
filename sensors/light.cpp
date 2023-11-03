#include "light.hpp"

void LightSensor::generateValue() { value = (rand() % 2 == 0); }

LightSensor::LightSensor() : Sensor(){};

LightSensor::LightSensor(const LightSensor& sensor) : Sensor(sensor) {}

LightSensor::LightSensor(std::string name, int interval)
    : Sensor(name, interval) {}

LightSensor& LightSensor::operator=(const LightSensor& sensor) {
    Sensor<bool>::operator=(sensor);
    return *this;
}
