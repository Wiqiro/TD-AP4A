#include "scheduler.hpp"

Scheduler::Scheduler()
    : server(nullptr),
      i_sensors(),
      f_sensors(),
      b_sensors(),
      is_running(false) {}

Scheduler::~Scheduler() {
    stop();
}

Scheduler &Scheduler::operator=(const Scheduler &scheduler) {
    server = scheduler.server;
    i_sensors = scheduler.i_sensors;
    f_sensors = scheduler.f_sensors;
    b_sensors = scheduler.b_sensors;

    return *this;
}

void Scheduler::linkServer(Server &server) { this->server = &server; }

void Scheduler::linkSensor(Sensor<int> &sensor) {
    i_sensors.push_back(&sensor);
}
void Scheduler::linkSensor(Sensor<float> &sensor) {
    f_sensors.push_back(&sensor);
}
void Scheduler::linkSensor(Sensor<bool> &sensor) {
    b_sensors.push_back(&sensor);
}

void Scheduler::unlinkSensor(std::string name) {
    i_sensors.remove_if(
        [&name](Sensor<int> *s) { return s->getName() == name; });
    f_sensors.remove_if(
        [&name](Sensor<float> *s) { return s->getName() == name; });
    b_sensors.remove_if(
        [&name](Sensor<bool> *s) { return s->getName() == name; });
}

bool Scheduler::start() {
    if (is_running) return true;

    is_running = true;
    try {
        data_collector = std::thread([this]() {
            while (is_running) {
                processSensorList(i_sensors);
                processSensorList(f_sensors);
                processSensorList(b_sensors);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    } catch (const std::system_error &error) {
        is_running = false;
    }
    return data_collector.joinable();
}

void Scheduler::stop() {
    if (is_running) {
        is_running = false;
        data_collector.join();
    }
}