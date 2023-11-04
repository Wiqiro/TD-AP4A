#include "humidity.hpp"

/**
 * @brief Génère une valeur de capteur aléatoire
 *
 */
void HumiditySensor::generateValue() {
    // Génération d'un float aléatoire entre 0 et 100
    value = ((float)rand() / RAND_MAX) * 100;
}

/**
 * @brief Constructeur par défaut de la classe HumiditySensor
 *
 */
HumiditySensor::HumiditySensor() : Sensor(){};

/**
 * @brief Constructeur par recopie de la classe HumiditySensor
 *
 * @param sensor le capteur d'humidité à copier
 */
HumiditySensor::HumiditySensor(const HumiditySensor& sensor) : Sensor(sensor) {}

/**
 * @brief Constructeur de la classe HumiditySensor
 *
 * @param name le nom du capteur d'humidité
 * @param interval l'intervalle de lecture du capteur d'humidité
 */
HumiditySensor::HumiditySensor(std::string name, u_int interval)
    : Sensor(name, interval) {}

/**
 * @brief Opérateur d'affectation de la classe HumiditySensor
 *
 * @param sensor le capteur d'humidité à copier
 * @return HumiditySensor& une référence à l'objet HumiditySensor copié
 */
HumiditySensor& HumiditySensor::operator=(const HumiditySensor& sensor) {
    Sensor<float>::operator=(sensor);
    return *this;
}
