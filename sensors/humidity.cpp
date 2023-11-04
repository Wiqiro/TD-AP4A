#include "humidity.hpp"

void HumiditySensor::generateValue() {
    // Génération d'un float aléatoire entre 0 et 100
    value = ((float)rand() / RAND_MAX) * 100;
}

HumiditySensor::HumiditySensor() : Sensor(){};

HumiditySensor::HumiditySensor(const HumiditySensor& sensor) : Sensor(sensor) {}

HumiditySensor::HumiditySensor(std::string name, u_int interval)
    : Sensor(name, interval) {}

HumiditySensor& HumiditySensor::operator=(const HumiditySensor& sensor) {
    Sensor<float>::operator=(sensor);
    return *this;
}
