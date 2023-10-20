#include "scheduler.h"

Scheduler::Scheduler() : server(), sensors() {}

Scheduler::~Scheduler() {}

Scheduler &Scheduler::operator=(const Scheduler &scheduler) {
    return *this;
}

void Scheduler::addSensor(Sensor *sensor) { sensors.push_back(sensor); }

void Scheduler::removeSensor(std::string name) {
    for (std::list<Sensor*>::iterator i = sensors.begin(); i != sensors.end();
         i++) {
        if ((*i)->getName() == name) {
            i = sensors.erase(i);
        }
    }
}