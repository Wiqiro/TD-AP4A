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
    HumiditySensor();
    HumiditySensor(const HumiditySensor& sensor);
    HumiditySensor(std::string name, int interval);
    ~HumiditySensor();

    HumiditySensor& operator=(const HumiditySensor& sensor);
};