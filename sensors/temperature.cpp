#include "temperature.hpp"

void TemperatureSensor::generateValue() {
    // Génération d'un float aléatoire entre -10 et 40
    value = ((float)rand() / RAND_MAX) * 50 - 10;
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
