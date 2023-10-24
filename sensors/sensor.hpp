#pragma once

#include <chrono>
#include <string>

template <typename T>
class Sensor {
   private:
    std::string name;
    int interval;
    std::chrono::time_point<std::chrono::system_clock> last_read_time;

    virtual void aleaGenVal() = 0;

   protected:
    T value;

   public:
    Sensor() : name("unnamed_sensor"), interval(1000), value() {}

    Sensor(const Sensor &sensor)
        : name(sensor.name), interval(sensor.interval), value(sensor.value) {}

    Sensor(std::string name, int interval)
        : name(name), interval(interval) {}
        
    ~Sensor() {}

    std::string getName() { return name; }

    T sendData() {
        aleaGenVal();
        return value;
    }

    void setInterval(int interval) { this->interval = interval; }

    bool isReady() {
        auto current_time = std::chrono::system_clock::now();
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                current_time - last_read_time);
        return elapsed_time.count() >= interval;
    }

    void updateTimer() { last_read_time = std::chrono::system_clock::now(); }
};