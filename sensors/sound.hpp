#include "./sensor.hpp"

class SoundSensor : public Sensor<int> {
    int aleaGenVal() { return 1; }
};