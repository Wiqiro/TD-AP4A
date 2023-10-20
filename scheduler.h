#pragma once

#include <list>

#include "sensors/sensor.h"
#include "server.h"

class Scheduler {
   private:
    Server server;
    std::list<Sensor*> sensors;


   public:
    Scheduler();
    Scheduler(const Scheduler &scheduler);
    ~Scheduler();

    Scheduler &operator=(const Scheduler &scheduler);

    void addSensor(Sensor *sensor);
    void removeSensor(std::string name);
};
