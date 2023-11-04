#include "light.hpp"

/**
 * @brief Génère une valeur de capteur aléatoire
 *
 */
void LightSensor::generateValue() {
    // Génération d'un booléen aléatoire
    value = (rand() % 2 == 0);
}

/**
 * @brief Constructeur par défaut de la classe LightSensor
 *
 */
LightSensor::LightSensor() : Sensor(){};

/**
 * @brief Constructeurpar recopie de la classe LightSensor
 *
 * @param sensor le capteur de lumière à copier
 */
LightSensor::LightSensor(const LightSensor& sensor) : Sensor(sensor) {}

/**
 * @brief Constructeur de la classe LightSensor
 *
 * @param name le nom du capteur de lumière
 * @param interval l'intervalle de lecture du capteur de lumière
 */
LightSensor::LightSensor(std::string name, u_int interval)
    : Sensor(name, interval) {}

/**
 * @brief Opérateur d'affectation de la classe LightSensor
 *
 * @param sensor le capteur de lumière à copier
 * @return LightSensor& une référence à l'objet LightSensor copié
 */
LightSensor& LightSensor::operator=(const LightSensor& sensor) {
    Sensor<bool>::operator=(sensor);
    return *this;
}
