#include "sensor.h"

int Sensor::aleaGenVal() {
    return 10;
}

Sensor::Sensor() : name("unnamed_sensor") {}

Sensor::Sensor(const Sensor &sensor) : name(sensor.name) {}

Sensor::Sensor(std::string name) : name(name) {}

Sensor::~Sensor() {}

int Sensor::sendData() {
    return aleaGenVal();
}

std::string Sensor::getName() {
    return name;
}
