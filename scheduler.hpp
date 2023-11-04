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
        // Pas obligé mais pour plus de visibilité
        Server &server = *this->server;
        for (Sensor<T> *sensor : sensor_list) {
            if (sensor->isReady()) {
                // On envoie les données du capteur vers le serveur si
                // l'intervalle du capteur est dépassée
                std::tuple<std::string, T> data = {sensor->getName(),
                                                   sensor->sendData()};
                server << data;
                sensor->updateTimer();
            }
        }
    }

   public:
    /**
     * @brief Constructeur par défaut de la classe Scheduler
     *
     */
    Scheduler();

    /**
     * @brief Constructeur par recopie de la classe Scheduler
     *
     * @param scheduler le scheduler à copier
     */
    Scheduler(const Scheduler &scheduler);

    /**
     * @brief Destructeur de la classe Scheduler
     *
     * Arrête la simulation si elle est en cours mais ne libère pas la mémoire
     * des capteurs et du serveur.
     */
    ~Scheduler();

    /**
     * @brief Opérateur d'affectation de la classe Scheduler
     *
     * @param scheduler le scheduler à copier
     * @return Scheduler& une référence au scheduler copié
     */
    Scheduler &operator=(const Scheduler &scheduler);

    /**
     * @brief Relie un server au scheduler
     *
     * @param server le serveur à relier au scheduler
     *
     * @warning Le serveur ne sera pas supprimé automatiquement lors de la
     * destruction: libérez manuellement le serveur ou appelez deleteServer()
     */
    void linkServer(Server *server);

    /**
     * @brief Relie un capteur de type int au scheduler
     *
     * @param sensor capteur à relier au scheduler
     *
     * @warning Le capteur ne sera pas supprimé automatiquement lors de la
     * destruction: libérez manuellement le serveur ou appelez deleteSensor()
     */
    void linkSensor(Sensor<int> *sensor);

    /**
     * @brief Relie un capteur de type float au scheduler
     *
     * @param sensor capteur à relier au scheduler
     *
     * @warning Le capteur ne sera pas supprimé automatiquement lors de la
     * destruction: libérez manuellement le serveur ou appelez deleteSensor()
     */
    void linkSensor(Sensor<float> *sensor);

    /**
     * @brief Relie un capteur de type bool au scheduler
     *
     * @param sensor capteur à relier au scheduler
     *
     * @warning Le capteur ne sera pas supprimé automatiquement lors de la
     * destruction: libérez manuellement le serveur ou appelez deleteSensor()
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
     * @return true si le lancement est réussi
     * @return false si le lancement n'est pas réussi
     */
    bool start();

    /**
     * @brief Arrête la simulation
     *
     */
    void stop();

    /**
     * @brief Permet de savoir si la simulation est en marche ou pas
     *
     * @return true si la simulation est en marche
     * @return false si la simulation est à l'arrêt
     */
    bool isRunning();

    /**
     * @brief Libère la mémoire du serveur
     *
     */
    void deleteServer();

    /**
     * @brief Libère la mémoire de l'intégralité des capteurs
     *
     */
    void deleteSensors();
};
