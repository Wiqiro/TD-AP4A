#include "./sensor.hpp"

class LightSensor : public Sensor<bool> {
    bool aleaGenVal() { return false; }
};