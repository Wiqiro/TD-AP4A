#pragma once

#include "./sensor.hpp"

class LightSensor : public Sensor<bool> {
   private:
    /**
     * @brief Génère une valeur de capteur aléatoire
     *
     */
    void generateValue();

   public:
    /**
     * @brief Constructeur par défaut de la classe LightSensor
     *
     */
    LightSensor();

    /**
     * @brief Constructeurpar recopie de la classe LightSensor
     *
     * @param sensor le capteur de lumière à copier
     */
    LightSensor(const LightSensor& sensor);

    /**
     * @brief Constructeur de la classe LightSensor
     *
     * @param name le nom du capteur de lumière
     * @param interval l'intervalle de lecture du capteur de lumière
     */
    LightSensor(std::string name, u_int interval);

    /**
     * @brief Destructeur de la classe LightSensor
     * 
     */
    ~LightSensor() = default;

    /**
     * @brief Opérateur d'affectation de la classe LightSensor
     *
     * @param sensor le capteur de lumière à copier
     * @return LightSensor& une référence à l'objet LightSensor copié
     */
    LightSensor& operator=(const LightSensor& sensor);
};