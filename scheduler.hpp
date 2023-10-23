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
    Server server;
    bool is_running;

    std::list<Sensor<int> *> i_sensors;
    std::list<Sensor<float> *> f_sensors;
    std::list<Sensor<bool> *> b_sensors;

    std::thread data_collector;

    template <typename T>
    void processSensorList(std::list<Sensor<T> *> sensor_list) {
        for (Sensor<T> *sensor : sensor_list) {
            if (sensor->isReady()) {
                std::string name = sensor->getName();
                T data = sensor->sendData();
                server.dataRcv(name, data);
                sensor->updateTimer();
            }
        }
    }

   public:
    Scheduler();
    Scheduler(const Scheduler &scheduler);
    ~Scheduler();

    Scheduler &operator=(const Scheduler &scheduler);

    void addSensor(Sensor<int> *sensor);
    void addSensor(Sensor<float> *sensor);
    void addSensor(Sensor<bool> *sensor);

    void removeSensor(std::string name);

    void start() {
        if (is_running) {
            return;
        }
        is_running = true;
        data_collector = std::thread([this]() {
            std::cout << "Hello" << std::endl;
            while (is_running) {
                processSensorList(i_sensors);
                processSensorList(f_sensors);
                processSensorList(b_sensors);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }

    void stop() {
        if (is_running) {
            is_running = false;
            data_collector.join();
        }
    }
};
