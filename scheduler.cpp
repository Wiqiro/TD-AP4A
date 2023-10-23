#include "scheduler.hpp"

Scheduler::Scheduler() : server(), i_sensors(), f_sensors(), b_sensors() {}

Scheduler::~Scheduler() {}

Scheduler &Scheduler::operator=(const Scheduler &scheduler) {
    server = scheduler.server;
    i_sensors = scheduler.i_sensors;
    f_sensors = scheduler.f_sensors;
    b_sensors = scheduler.b_sensors;

    return *this;
}

void Scheduler::addSensor(Sensor<int> *sensor) {
    if (sensor) i_sensors.push_back(sensor);
}
void Scheduler::addSensor(Sensor<float> *sensor) {
    if (sensor) f_sensors.push_back(sensor);
}
void Scheduler::addSensor(Sensor<bool> *sensor) {
    if (sensor) b_sensors.push_back(sensor);
}

void Scheduler::removeSensor(std::string name) {
    i_sensors.remove_if(
        [&name](Sensor<int> *s) { return s->getName() == name; });
    f_sensors.remove_if(
        [&name](Sensor<float> *s) { return s->getName() == name; });
    b_sensors.remove_if(
        [&name](Sensor<bool> *s) { return s->getName() == name; });
}
