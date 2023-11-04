#include <ctime>
#include <cctype>

#include "scheduler.hpp"
#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

// Macro permettant de CLEAR_CONSOLE la console
#ifdef _WIN32
#include <windows.h>
#define CLEAR_CONSOLE() std::system("cls")
#else
#define CLEAR_CONSOLE() std::system("clear")
#endif

// Macro permettant de nettoyer le flux d'entrée
#define FLUSH_CIN() \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

/**
 * @brief Ajoute un capteur au scheduler suivant les entrées de l'utilisateur
 *
 * @param scheduler scheduler à qui on va link le nouveau capteur
 * @return true si les inputs sont correctes
 * @return false si les inputs sont incorrectes
 */
bool addSensorFromInput(Scheduler &scheduler) {
    int sensor_type;
    std::string sensor_name;
    u_int sensor_interval;

    std::cout << "Choisissez le type du capteur" << std::endl
              << "Temperature = 1, Humidité = 2, Son = 3, Lumière = 4: ";

    std::cin >> sensor_type;
    FLUSH_CIN();
    if (std::cin.fail() || sensor_type < 1 || sensor_type > 4) {
        std::cin.clear();
        return false;
    }

    std::cout << "Choisissez le nom du capteur: ";
    std::cin >> sensor_name;

    std::cout << "Choisissez l'intervalle de lecture du capteur en ms: ";
    std::cin >> sensor_interval;
    FLUSH_CIN();
    if (std::cin.fail()) {
        std::cin.clear();
        return false;
    }

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
            SoundSensor *sensor = new SoundSensor(sensor_name, sensor_interval);
            scheduler.linkSensor(sensor);
            break;
        }
        case 4: {
            LightSensor *sensor = new LightSensor(sensor_name, sensor_interval);
            scheduler.linkSensor(sensor);
            break;
        }
        default:
            break;
    }
    return true;
}

int main() {
    // Initialisation la génération de nombre aléatoire pour les capteurs
    srand(time(nullptr));
    CLEAR_CONSOLE();

    // Création du scheduler avec le constructeur par défaut
    Scheduler scheduler;

    std::string logs_path("");
    bool console_activation(true), logs_activation(true);
    char char_buffer;

    std::cout << "Voulez-vous activer le retour console ? (O/n) ";
    std::cin >> char_buffer;
    FLUSH_CIN();
    if (toupper(char_buffer) == 'N') console_activation = false;

    std::cout << "Voulez-vous activer les logs ? (O/n) ";
    std::cin >> char_buffer;
    FLUSH_CIN();
    if (toupper(char_buffer) == 'N') {
        logs_activation = false;
    } else {
        std::cout << "Donnez le chemin de votre dossier de logs: ";
        std::cin >> logs_path;
        FLUSH_CIN();
    }

    // On créé le serveur à partir des paramètres entrés par l'utilisateur
    Server *server = new Server(logs_path, console_activation, logs_activation);
    // On lie le serveur au scheduler
    scheduler.linkServer(server);

    CLEAR_CONSOLE();
    // Boucle de création des capteurs
    while (true) {
        if (addSensorFromInput(scheduler)) {
            std::cout << "Voules-vous ajouter de nouveaux capteurs ? (O/n) ";
            std::cin >> char_buffer;
            FLUSH_CIN();
            if (toupper(char_buffer) == 'N') {
                break;
            } else {
                CLEAR_CONSOLE();
            }
        } else {
            std::cout << "Erreur lors de la saisie des informations, veuillez "
                         "rééssayer "
                      << std::endl
                      << std::endl;
        }
    }

    CLEAR_CONSOLE();
    std::cout << "Pour commencer la simulation: L" << std::endl
              << "Pour pauser la simulation: P" << std::endl
              << "Pour nettoyer la console: C" << std::endl
              << "Pour quitter le programme: Q" << std::endl
              << std::endl;

    bool running = true;

    // Boucle principale qui gère le scheduler en fonction des inputs
    while (running) {
        std::cin >> char_buffer;
        FLUSH_CIN();
        switch (toupper(char_buffer)) {
            case 'L':
                CLEAR_CONSOLE();
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
                CLEAR_CONSOLE();
                break;
            case 'Q':
                running = false;
                break;
            default:
                break;
        }
    }

    std::cout << "Fin du programme" << std::endl;
    // On stoppe le scheduler
    scheduler.stop();
    // On libère l'intégralité des capteurs alloués plutôt
    scheduler.deleteSensors();
    // On libère le serveur
    scheduler.deleteServer();

    return 0;
}
