#pragma once

#include <list>

#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

class Scheduler {
   private:
    Server server;

    std::list<HumiditySensor *> h_sensors;
    std::list<LightSensor *> l_sensors;
    std::list<SoundSensor *> s_sensors;
    std::list<TemperatureSensor *> t_sensors;

   public:
    Scheduler();
    Scheduler(const Scheduler &scheduler);
    ~Scheduler();

    Scheduler &operator=(const Scheduler &scheduler);

    void addSensor(HumiditySensor *sensor);
    void addSensor(LightSensor *sensor);
    void addSensor(SoundSensor *sensor);
    void addSensor(TemperatureSensor *sensor);

    void removeSensor(std::string name);
};
