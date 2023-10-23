#pragma once

#include "./sensor.hpp"

class HumiditySensor : public Sensor<float> {
    void aleaGenVal() {
        value = ((float) rand() / RAND_MAX) * 100;
    }
};