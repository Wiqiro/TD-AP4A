#include "temperature.hpp"

void TemperatureSensor::generateValue() {
    value = ((float)rand() / RAND_MAX) * 100 - 50;
}

TemperatureSensor::TemperatureSensor() : Sensor(){};

TemperatureSensor::TemperatureSensor(const TemperatureSensor& sensor)
    : Sensor(sensor) {}

TemperatureSensor::TemperatureSensor(std::string name, int interval)
    : Sensor(name, interval) {}

TemperatureSensor& TemperatureSensor::operator=(
    const TemperatureSensor& sensor) {
    Sensor<float>::operator=(sensor);
    return *this;
}
