#include "sound.hpp"

void SoundSensor::generateValue() {
    // Génération d'un entier aléatoire entre 40 et 80
    value = rand() % 40 + 40;
}

SoundSensor::SoundSensor() : Sensor(){};

SoundSensor::SoundSensor(const SoundSensor& sensor) : Sensor(sensor) {}

SoundSensor::SoundSensor(std::string name, int interval)
    : Sensor(name, interval) {}

SoundSensor& SoundSensor::operator=(const SoundSensor& sensor) {
    Sensor<int>::operator=(sensor);
    return *this;
}
