#include "humidity.hpp"

void HumiditySensor::generateValue() { value = ((float)rand() / RAND_MAX) * 100; }

HumiditySensor::HumiditySensor() : Sensor(){};

HumiditySensor::HumiditySensor(const HumiditySensor& sensor) : Sensor(sensor) {}

HumiditySensor::HumiditySensor(std::string name, int interval)
    : Sensor(name, interval) {}
    
HumiditySensor::~HumiditySensor() {}

HumiditySensor& HumiditySensor::operator=(const HumiditySensor& sensor) {
    if (this != &sensor) {
        Sensor<float>::operator=(sensor);
    }
    return *this;
}