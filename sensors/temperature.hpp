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
    TemperatureSensor();
    TemperatureSensor(const TemperatureSensor& sensor);
    TemperatureSensor(std::string name, int interval);
    ~TemperatureSensor() = default;

    TemperatureSensor& operator=(const TemperatureSensor& sensor);
};
