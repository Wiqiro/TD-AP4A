#include "scheduler.hpp"

/**
 * @brief Constructeur par défaut de la classe Scheduler
 *
 */
Scheduler::Scheduler()
    : server(nullptr),
      i_sensors(),
      f_sensors(),
      b_sensors(),
      is_running(false),
      data_collector() {}

/**
 * @brief Constructeur par recopie de la classe Scheduler
 *
 * @param scheduler le scheduler à copier
 */
Scheduler::Scheduler(const Scheduler &scheduler)
    : server(scheduler.server),
      i_sensors(scheduler.i_sensors),
      f_sensors(scheduler.f_sensors),
      b_sensors(scheduler.b_sensors),
      is_running(false),
      data_collector() {}

/**
 * @brief Destructeur de la classe Scheduler
 *
 * Arrête la simulation si elle est en cours mais ne libère pas la mémoire
 * des capteurs et du serveur.
 */
Scheduler::~Scheduler() { stop(); }

/**
 * @brief Opérateur d'affectation de la classe Scheduler
 *
 * @param scheduler le scheduler à copier
 * @return Scheduler& une référence au scheduler copié
 */
Scheduler &Scheduler::operator=(const Scheduler &scheduler) {
    server = scheduler.server;
    i_sensors = scheduler.i_sensors;
    f_sensors = scheduler.f_sensors;
    b_sensors = scheduler.b_sensors;

    return *this;
}

/**
 * @brief Relie un server au scheduler
 *
 * @param server le serveur à relier au scheduler
 *
 * @warning Le serveur ne sera pas supprimé automatiquement lors de la
 * destruction: libérez manuellement le serveur ou appelez deleteServer()
 */
void Scheduler::linkServer(Server *server) { this->server = server; }

/**
 * @brief Relie un capteur de type int au scheduler
 *
 * @param sensor capteur à relier au scheduler
 *
 * @warning Le capteur ne sera pas supprimé automatiquement lors de la
 * destruction: libérez manuellement le serveur ou appelez deleteSensor()
 */
void Scheduler::linkSensor(Sensor<int> *sensor) { i_sensors.push_back(sensor); }

/**
 * @brief Relie un capteur de type float au scheduler
 *
 * @param sensor capteur à relier au scheduler
 *
 * @warning Le capteur ne sera pas supprimé automatiquement lors de la
 * destruction: libérez manuellement le serveur ou appelez deleteSensor()
 */
void Scheduler::linkSensor(Sensor<float> *sensor) {
    f_sensors.push_back(sensor);
}

/**
 * @brief Relie un capteur de type bool au scheduler
 *
 * @param sensor capteur à relier au scheduler
 *
 * @warning Le capteur ne sera pas supprimé automatiquement lors de la
 * destruction: libérez manuellement le serveur ou appelez deleteSensor()
 */
void Scheduler::linkSensor(Sensor<bool> *sensor) {
    b_sensors.push_back(sensor);
}

/**
 * @brief Dissocie un capteur du scheduler
 *
 * @param name nom du capteur à dissocier
 */
void Scheduler::unlinkSensor(std::string &name) {
    i_sensors.remove_if(
        [&name](Sensor<int> *s) { return s->getName() == name; });
    f_sensors.remove_if(
        [&name](Sensor<float> *s) { return s->getName() == name; });
    b_sensors.remove_if(
        [&name](Sensor<bool> *s) { return s->getName() == name; });
}

/**
 * @brief Lance la simulation
 *
 * @return true si le lancement est réussi
 * @return false si le lancement n'est pas réussi
 */
bool Scheduler::start() {
    if (!server) return false;
    if (is_running) return true;

    try {
        is_running = true;
        // On créé un nouveau thread qui va parcourir les listes de capteurs
        // pour les traiter toutes les millisecondes
        data_collector = std::thread([this]() {
            while (is_running) {
                processSensorList(i_sensors);
                processSensorList(f_sensors);
                processSensorList(b_sensors);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    } catch (const std::system_error &error) {
        // On teste si il y a eu un problème lors de la création du thread
        is_running = false;
    }

    if (!data_collector.joinable()) is_running = false;
    return is_running;
}

/**
 * @brief Arrête la simulation
 *
 */
void Scheduler::stop() {
    if (is_running) {
        is_running = false;
        data_collector.join();
    }
}

/**
 * @brief Permet de savoir si la simulation est en marche ou pas
 *
 * @return true si la simulation est en marche
 * @return false si la simulation est à l'arrêt
 */
bool Scheduler::isRunning() { return is_running; }

/**
 * @brief Libère la mémoire du serveur
 *
 */
void Scheduler::deleteServer() {
    if (server) delete server;
}

/**
 * @brief Libère la mémoire de l'intégralité des capteurs
 *
 */
void Scheduler::deleteSensors() {
    if (is_running) stop();

    for (auto *s : i_sensors) delete s;
    for (auto *s : f_sensors) delete s;
    for (auto *s : b_sensors) delete s;
}