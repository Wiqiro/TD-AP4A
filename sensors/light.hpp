#pragma once

#include "./sensor.hpp"

class LightSensor : public Sensor<bool> {
   private:
    void aleaGenVal();

   public:
    LightSensor();
    LightSensor(const LightSensor& sensor);
    LightSensor(std::string name, int interval);
    ~LightSensor();

    LightSensor& operator=(const LightSensor& sensor);
};