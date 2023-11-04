#pragma once

#include "./sensor.hpp"

class SoundSensor : public Sensor<int> {
   private:
    /**
     * @brief Génère une valeur de capteur aléatoire
     *
     */
    void generateValue();

   public:
    /**
     * @brief Constructeur par défaut de la classe SoundSensor
     *
     */
    SoundSensor();

    /**
     * @brief Constructeur par recopie de la classe SoundSensor
     *
     * @param sensor le capteur de son à copier
     */
    SoundSensor(const SoundSensor& sensor);

    /**
     * @brief Constructeur de la classe SoundSensor
     *
     * @param name le nom du capteur de son
     * @param interval l'intervalle de lecture du capteur de son
     */
    SoundSensor(std::string name, u_int interval);

    /**
     * @brief Destructeur de la classe SoundSensor
     *
     */
    ~SoundSensor() = default;

    /**
     * @brief Opérateur d'affectation de la classe SoundSensor
     *
     * @param sensor le capteur de son à copier
     * @return SoundSensor& une référence à l'objet SoundSensor copié
     */
    SoundSensor& operator=(const SoundSensor& sensor);
};