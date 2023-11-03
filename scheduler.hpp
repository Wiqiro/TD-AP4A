#pragma once

#include <list>
#include <thread>
#include <tuple>

#include "sensors/humidity.hpp"
#include "sensors/light.hpp"
#include "sensors/sensor.hpp"
#include "sensors/sound.hpp"
#include "sensors/temperature.hpp"
#include "server.hpp"

class Scheduler {
   private:
    Server *server;

    // On doit créer une liste pour chaque type de capteur
    std::list<Sensor<int> *> i_sensors;
    std::list<Sensor<float> *> f_sensors;
    std::list<Sensor<bool> *> b_sensors;

    bool is_running;
    // Thread qui permettra de récupérer la valeur des capteurs en paralèlle de
    // l'exécution du programme
    std::thread data_collector;

    /**
     * @brief Parcours une liste de capteurs et envoie leurs données au serveur
     * losqu'elles sont prêtes à être récupérées
     *
     * @tparam T type contenu dans la liste de capteurs
     * @param sensor_list liste de capteurs à traiter
     */
    template <typename T>
    void processSensorList(std::list<Sensor<T> *> &sensor_list) {
        Server &server = *this->server;
        for (Sensor<T> *sensor : sensor_list) {
            if (sensor->isReady()) {
                std::tuple<std::string, T> data = {sensor->getName(),
                                                   sensor->sendData()};
                server << data;
                sensor->updateTimer();
            }
        }
    }


   public:
    Scheduler();
    Scheduler(const Scheduler &scheduler);
    ~Scheduler();

    Scheduler &operator=(const Scheduler &scheduler);

    /**
     * @brief Relie un server au scheduler
     *
     * @param server le serveur à relier au scheduler
     */
    void linkServer(Server *server);

    /**
     * @brief Relie un capteur au scheduler
     *
     * @param sensor capteur à relier au scheduler
     */
    void linkSensor(Sensor<int> *sensor);

    /**
     * @brief Relie un capteur au scheduler
     *
     * @param sensor capteur à relier au scheduler
     */
    void linkSensor(Sensor<float> *sensor);

    /**
     * @brief Relie un capteur au scheduler
     *
     * @param sensor capteur à relier au scheduler
     */
    void linkSensor(Sensor<bool> *sensor);

    /**
     * @brief Dissocie un capteur du scheduler
     *
     * @param name nom du capteur à dissocier
     */
    void unlinkSensor(std::string &name);

    /**
     * @brief Lance la simulation
     *
     * @return true si le lancement est réussi et
     * @return false si le lancement n'est pas réussi
     */
    bool start();

    /**
     * @brief Arrête la simulation
     *
     */
    void stop();

    bool isRunning();

    void deleteServer();

    void deleteSensors();
};
