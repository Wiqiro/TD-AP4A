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

    HumiditySensor cave_humidity("cave_humidity", 1000);
    SoundSensor sound_sensor("sound_sensor", 2000);
    /* LightSensor day_sensor("day_sensor", 5000); */
    TemperatureSensor house_temperature("house_temperature", 9090);

    Server server("./logs/", true, true);

    Scheduler scheduler;
    scheduler.linkServer(server);
    scheduler.linkSensor(cave_humidity);
    scheduler.linkSensor(sound_sensor);
    scheduler.linkSensor(house_temperature);

    scheduler.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    scheduler.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    scheduler.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  


    return 0;
}