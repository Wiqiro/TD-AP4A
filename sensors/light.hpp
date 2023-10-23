#pragma once

#include "./sensor.hpp"

class LightSensor : public Sensor<bool> {
    void aleaGenVal() {
        value = (rand() % 2 == 0);
    }
};