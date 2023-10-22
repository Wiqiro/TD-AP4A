#include "scheduler.hpp"

Scheduler::Scheduler()
    : server(), h_sensors(), l_sensors(), s_sensors(), t_sensors() {}

Scheduler::~Scheduler() {}

Scheduler &Scheduler::operator=(const Scheduler &scheduler) {
    return *this;
}  // TODO

void Scheduler::addSensor(HumiditySensor *sensor) {
    h_sensors.push_back(sensor);
}
void Scheduler::addSensor(LightSensor *sensor) { l_sensors.push_back(sensor); }
void Scheduler::addSensor(SoundSensor *sensor) { s_sensors.push_back(sensor); }
void Scheduler::addSensor(TemperatureSensor *sensor) {
    t_sensors.push_back(sensor);
}

void Scheduler::removeSensor(std::string name) {
    h_sensors.remove_if(
        [&name](HumiditySensor *s) { return s->getName() == name; });
    l_sensors.remove_if(
        [&name](LightSensor *s) { return s->getName() == name; });
    s_sensors.remove_if(
        [&name](SoundSensor *s) { return s->getName() == name; });
    t_sensors.remove_if(
        [&name](TemperatureSensor *s) { return s->getName() == name; });
}
