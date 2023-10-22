#include "./sensor.hpp"

class HumiditySensor : public Sensor<float> {
    float aleaGenVal() { return 5.2; }
};