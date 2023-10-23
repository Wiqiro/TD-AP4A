#pragma once

#include "./sensor.hpp"

class TemperatureSensor : public Sensor<float> {
    void aleaGenVal() {
        value = ((float) rand() / RAND_MAX) * 100 - 50;
    }
};