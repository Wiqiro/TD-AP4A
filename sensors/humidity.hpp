#pragma once

#include "./sensor.hpp"

class HumiditySensor : public Sensor<float> {
   private:
    /**
     * @brief Génère une valeur de capteur aléatoire
     *
     */
    void generateValue();

   public:
    /**
     * @brief Constructeur par défaut de la classe HumiditySensor
     *
     */
    HumiditySensor();

    /**
     * @brief Constructeur par recopie de la classe HumiditySensor
     *
     * @param sensor le capteur d'humidité à copier
     */
    HumiditySensor(const HumiditySensor& sensor);

    /**
     * @brief Constructeur de la classe HumiditySensor
     *
     * @param name le nom du capteur d'humidité
     * @param interval l'intervalle de lecture du capteur d'humidité
     */
    HumiditySensor(std::string name, u_int interval);

    /**
     * @brief Destructeur de la classe HumiditySensor
     *
     */
    ~HumiditySensor() = default;

    /**
     * @brief Opérateur d'affectation de la classe HumiditySensor
     *
     * @param sensor le capteur d'humidité à copier
     * @return HumiditySensor& une référence à l'objet HumiditySensor copié
     */
    HumiditySensor& operator=(const HumiditySensor& sensor);
};