#include <cctype>
#include <ctime>
#include <thread>

#include "scheduler.hpp"
#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

// Macro permettant de clear la console
#ifdef _WIN32
#include <windows.h>
#define CLEAR() std::system("cls")
#else
#define CLEAR() std::system("clear")
#endif

int main() {
    srand(time(nullptr));

    Scheduler scheduler;

    std::string logsFolderPath;
    std::cout
        << "Donnez le chemin du dosser où vous souhaitez stocker vos logs: ";
    std::cin >> logsFolderPath;
    Server *server = new Server(logsFolderPath, true, true);
    scheduler.linkServer(server);

    while (true) {
        int sensor_type;
        std::string sensor_name;
        int sensor_interval;

        CLEAR();
        std::cout << "Choisissez le type du capteur que vous souhaitez ajouter"
                  << std::endl
                  << "Temperature = 1, Humidité = 2, Son = 3, Lumière = 4: ";
        std::cin >> sensor_type;

        std::cout
            << "Choisissez le nom du capteur que vous souhaitez ajouter: ";
        std::cin >> sensor_name;

        std::cout << "Choisissez l'intervalle de lecture du capteur que vous "
                     "souhaitez ajouter: ";
        std::cin >> sensor_interval;

        switch (sensor_type) {
            case 1: {
                TemperatureSensor *sensor =
                    new TemperatureSensor(sensor_name, sensor_interval);
                scheduler.linkSensor(sensor);
                break;
            }
            case 2: {
                HumiditySensor *sensor =
                    new HumiditySensor(sensor_name, sensor_interval);
                scheduler.linkSensor(sensor);
                break;
            }
            case 3: {
                SoundSensor *sensor =
                    new SoundSensor(sensor_name, sensor_interval);
                scheduler.linkSensor(sensor);
                break;
            }
            case 4: {
                LightSensor *sensor =
                    new LightSensor(sensor_name, sensor_interval);
                scheduler.linkSensor(sensor);
                break;
            }
            default:
                break;
        }
        char buffer;

        std::cout << "Voules-vous ajouter de nouveaux capteurs ? (O/n) ";
        std::cin >> buffer;
        if (toupper(buffer) == 'N') {
            break;
        }
    }

    CLEAR();
    std::cout << "Pour commencer la simulation: L" << std::endl
              << "Pour pauser la simulation: P" << std::endl
              << "Pour nettoyer la console: C" << std::endl
              << "Pour quitter le programme: Q" << std::endl
              << std::endl;

    bool running = true;
    while (running) {
        char buffer;
        std::cin >> buffer;
        switch (toupper(buffer)) {
            case 'L':
            CLEAR();
                if (!scheduler.isRunning()) {
                    if (scheduler.start()) {
                        std::cout << "Simulation en marche" << std::endl;
                    } else {
                        std::cerr << "Erreur lors du lancement de la simulation"
                                  << std::endl;
                        running = false;
                    }
                }
                break;
            case 'P':
                if (scheduler.isRunning()) {
                    std::cout << "Simulation en pause" << std::endl;
                    scheduler.stop();
                }
                break;
            case 'C':
                CLEAR();
                break;
            case 'Q':
                running = false;
                break;
            default:
                break;
        }
    }

    std::cout << "Fin du programme" << std::endl;
    scheduler.stop();
    scheduler.deleteSensors();
    scheduler.deleteServer();

    return 0;
}
