#pragma once

#include <chrono>
#include <string>

template <typename T>
class Sensor {
   private:
    std::string name;
    int interval;

    // Dernière fois que le capteur a été lu
    std::chrono::time_point<std::chrono::system_clock> last_read_time;

    /**
     * @brief Génère une valeur de capteur aléatoire
     * 
     */
    virtual void generateValue() = 0;

   protected:
    T value;

   public:
    Sensor() : name("unnamed_sensor"), interval(1000), value(0) { updateTimer(); }

    Sensor(const Sensor &sensor)
        : name(sensor.name), interval(sensor.interval), value(sensor.value) {
        updateTimer();
    }

    Sensor(std::string name, int interval) : name(name), interval(interval), value(0) {
        updateTimer();
    }

    ~Sensor() {}

    Sensor &operator=(const Sensor &sensor) {
        name = sensor.name;
        interval = sensor.interval;
        value = sensor.value;
        updateTimer();
        return *this;
    }

    /**
     * @brief Retourne le nom du capteur
     * 
     * @return std::string: Le nom du capteur
     */
    std::string getName() { return name; }

    /**
     * @brief Envoie la valeur du capteur
     * 
     * @return T: La valeur du capteur
     */
    T sendData() {
        generateValue();
        return value;
    }

    /**
     * @brief Change l'intervalle de lecture du capteur par le scheduler
     * 
     * @param interval intervalle de lecture du capteur
     */
    void setInterval(int interval) { this->interval = interval; }

    /**
     * @brief Permet de savoir si le capteur peut être lu à nouveau
     * 
     * @return true si l'intervalle de temps est passée et
     * @return false sinon
     */
    bool isReady() {
        auto current_time = std::chrono::system_clock::now();
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                current_time - last_read_time);
        return elapsed_time.count() >= interval;
    }

    /**
     * @brief Met à jour le temps de dernière lecture du capteur
     * 
     */
    void updateTimer() { last_read_time = std::chrono::system_clock::now(); }
};