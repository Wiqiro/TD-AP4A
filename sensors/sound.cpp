#include "sound.hpp"

/**
 * @brief Génère une valeur de capteur aléatoire
 *
 */
void SoundSensor::generateValue() {
    // Génération d'un entier aléatoire entre 40 et 80
    value = rand() % 40 + 40;
}

/**
 * @brief Constructeur par défaut de la classe SoundSensor
 *
 */
SoundSensor::SoundSensor() : Sensor(){};

/**
 * @brief Constructeur par recopie de la classe SoundSensor
 *
 * @param sensor le capteur de son à copier
 */
SoundSensor::SoundSensor(const SoundSensor& sensor) : Sensor(sensor) {}

/**
 * @brief Constructeur de la classe SoundSensor
 *
 * @param name le nom du capteur de son
 * @param interval l'intervalle de lecture du capteur de son
 */
SoundSensor::SoundSensor(std::string name, u_int interval)
    : Sensor(name, interval) {}

/**
 * @brief Opérateur d'affectation de la classe SoundSensor
 *
 * @param sensor le capteur de son à copier
 * @return SoundSensor& une référence à l'objet SoundSensor copié
 */
SoundSensor& SoundSensor::operator=(const SoundSensor& sensor) {
    Sensor<int>::operator=(sensor);
    return *this;
}
