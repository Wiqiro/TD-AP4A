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
    SoundSensor();
    SoundSensor(const SoundSensor& sensor);
    SoundSensor(std::string name, u_int interval);
    ~SoundSensor() = default;

    SoundSensor& operator=(const SoundSensor& sensor);
};
