#include "temperature.hpp"

/**
 * @brief Génère une valeur de capteur aléatoire
 *
 */
void TemperatureSensor::generateValue() {
    // Génération d'un float aléatoire entre -10 et 40
    value = ((float)rand() / RAND_MAX) * 50 - 10;
}

/**
 * @brief Constructeur par défaut de la classe TemperatureSensor
 *
 */
TemperatureSensor::TemperatureSensor() : Sensor(){};

/**
 * @brief Constructeur par recopie de la classe TemperatureSensor
 *
 * @param sensor le capteur de température à copier
 */
TemperatureSensor::TemperatureSensor(const TemperatureSensor& sensor)
    : Sensor(sensor) {}

/**
 * @brief Constructeur de la classe TemperatureSensor
 *
 * @param name le nom du capteur de température
 * @param interval l'intervalle de lecture du capteur de température
 */
TemperatureSensor::TemperatureSensor(std::string name, u_int interval)
    : Sensor(name, interval) {}

/**
 * @brief Opérateur d'affectation de la classe TemperatureSensor
 *
 * @param sensor le capteur de température à copier
 * @return TemperatureSensor& une référence à l'objet TemperatureSensor
 * copié
 */
TemperatureSensor& TemperatureSensor::operator=(
    const TemperatureSensor& sensor) {
    Sensor<float>::operator=(sensor);
    return *this;
}
