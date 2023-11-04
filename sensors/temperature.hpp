#pragma once

#include "./sensor.hpp"

class TemperatureSensor : public Sensor<float> {
   private:
    /**
     * @brief Génère une valeur de capteur aléatoire
     *
     */
    void generateValue();

   public:
    /**
     * @brief Constructeur par défaut de la classe TemperatureSensor
     *
     */
    TemperatureSensor();

    /**
     * @brief Constructeur par recopie de la classe TemperatureSensor
     *
     * @param sensor le capteur de température à copier
     */
    TemperatureSensor(const TemperatureSensor& sensor);

    /**
     * @brief Constructeur de la classe TemperatureSensor
     *
     * @param name le nom du capteur de température
     * @param interval l'intervalle de lecture du capteur de température
     */
    TemperatureSensor(std::string name, u_int interval);

    /**
     * @brief Destructeur de la classe TemperatureSensor
     *
     */
    ~TemperatureSensor() = default;

    /**
     * @brief Opérateur d'affectation de la classe TemperatureSensor
     *
     * @param sensor le capteur de température à copier
     * @return TemperatureSensor& une référence à l'objet TemperatureSensor
     * copié
     */
    TemperatureSensor& operator=(const TemperatureSensor& sensor);
};