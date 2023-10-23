#include <ctime>
#include <thread>

#include "scheduler.hpp"
#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

int main() {
    srand(time(nullptr));

    Scheduler scheduler;

    HumiditySensor h_sens;
    SoundSensor s_sens;

    scheduler.addSensor(&h_sens);
    scheduler.addSensor(&s_sens);

    scheduler.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    scheduler.stop();

    return 0;
}