#pragma once

#include "./sensor.hpp"

class TemperatureSensor : public Sensor<float> {
   private:
    void aleaGenVal();

   public:
    TemperatureSensor();
    TemperatureSensor(const TemperatureSensor& sensor);
    TemperatureSensor(std::string name, int interval);
    ~TemperatureSensor();

    TemperatureSensor& operator=(const TemperatureSensor& sensor);
};