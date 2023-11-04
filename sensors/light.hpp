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
    LightSensor();
    LightSensor(const LightSensor& sensor);
    LightSensor(std::string name, u_int interval);
    ~LightSensor() = default;

    LightSensor& operator=(const LightSensor& sensor);
};
