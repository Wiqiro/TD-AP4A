#pragma once

#include "./sensor.hpp"

class SoundSensor : public Sensor<int> {
    void aleaGenVal() {
        value = rand()%100 + 30;
    }
};