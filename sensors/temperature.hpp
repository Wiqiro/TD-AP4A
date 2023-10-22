#include "./sensor.hpp"

class TemperatureSensor : public Sensor<float> {
    float aleaGenVal() { return 5.2; }
};