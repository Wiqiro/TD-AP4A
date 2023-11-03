#include "sound.hpp"

void SoundSensor::generateValue() { value = rand() % 100 + 30; }

SoundSensor::SoundSensor() : Sensor(){};

SoundSensor::SoundSensor(const SoundSensor& sensor) : Sensor(sensor) {}

SoundSensor::SoundSensor(std::string name, int interval)
    : Sensor(name, interval) {}

SoundSensor& SoundSensor::operator=(const SoundSensor& sensor) {
    Sensor<int>::operator=(sensor);
    return *this;
}
