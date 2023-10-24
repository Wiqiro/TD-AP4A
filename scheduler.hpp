#pragma once

#include <list>
#include <thread>

#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

class Scheduler {
   private:
    Server *server;

    std::list<Sensor<int> *> i_sensors;
    std::list<Sensor<float> *> f_sensors;
    std::list<Sensor<bool> *> b_sensors;

    bool is_running;
    std::thread data_collector;

    template <typename T>
    void processSensorList(std::list<Sensor<T> *> sensor_list) {
        for (Sensor<T> *sensor : sensor_list) {
        if (sensor->isReady()) {
            std::string name = sensor->getName();
            T data = sensor->sendData();
            server->recieveData(name, data);
            sensor->updateTimer();
        }
    }
    }

   public:
    Scheduler();
    Scheduler(const Scheduler &scheduler);
    ~Scheduler();

    Scheduler &operator=(const Scheduler &scheduler);

    void linkServer(Server &server);

    void linkSensor(Sensor<int> &sensor);
    void linkSensor(Sensor<float> &sensor);
    void linkSensor(Sensor<bool> &sensor);

    void unlinkSensor(std::string name);

    void start();
    void stop();
};
