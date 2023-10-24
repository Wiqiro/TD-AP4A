#pragma once

#include "./sensor.hpp"

class SoundSensor : public Sensor<int> {
   private:
    void aleaGenVal();

   public:
    SoundSensor();
    SoundSensor(const SoundSensor& sensor);
    SoundSensor(std::string name, int interval);
    ~SoundSensor();

    SoundSensor& operator=(const SoundSensor& sensor);
};