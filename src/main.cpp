#include "car_semaphore.hpp"
#include "electric_station.hpp"
#include "queue_queue.hpp"
#include "car_station.hpp"
#include "people_dinner.hpp"
#include "spsc_queue.hpp"
#include "gas_station.hpp"
#include "json.hpp"
#include <chrono>
#include <random>
#include <fstream>
#include <thread>

#include "test.hpp"

using nlohmann::json;

void generate_random_car_files(const std::string& directory) {
    std::filesystem::create_directories(directory);

    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int> idDist(1000, 9999);
    std::bernoulli_distribution boolDist(0.5);
    std::uniform_int_distribution<int> typeDist(0, 1);

    std::string id = "car_" + std::to_string(idDist(rng));

    bool needsDining  = boolDist(rng);
    bool needsRefuel  = boolDist(rng);
    int  typeValue    = typeDist(rng);

    json j;
    j["id"]            = id;
    j["needsDining"]   = needsDining;
    j["needsRefuel"]   = needsRefuel;
    j["type"]          = (typeValue == 0 ? "gas" : "electric");

    std::string filename = directory + "/" + id + ".json";
    std::ofstream out(filename);
    out << j.dump(4);
}

void scan_and_push_cars(const std::string& directory, SPSCQueue<Car>& queue) {
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;
        const fs::path& path = entry.path();

        std::ifstream in(path);
        if (!in) continue;

        json j;
        try {
            in >> j;
        } catch (...) {
            continue;
        }

        Car c = Car::parseCarFromJson(j);
        while (!queue.try_push(std::move(c))) {
            std::this_thread::yield();
        }

        fs::remove(path);
    }
}

int main() {
    SPSCQueue<Car> shared_queue;
    std::thread producer([&shared_queue]() {
        while (true) {
            scan_and_push_cars("data", shared_queue);
        }
    });

    std::thread consumer([&shared_queue]() {
        PeopleDinner people_dinner;
        GasStation gas_station;
        ElectricStation electric_station;

        Queue<Car> gasQueue;
        Queue<Car> electricQueue;
        CarStation gasStationForPeople(
            people_dinner,
            gas_station,
            gasQueue
        );

        CarStation electricStationForPeople(
            people_dinner,
            electric_station,
            electricQueue
        );

        CarSemaphore router(gasStationForPeople, electricStationForPeople);

        int i = 0;
        while (true) {
            Car car;
            if (shared_queue.try_pop(car)) {
                router.routeCar(car);
                std::cout << ++i << '\n';
            }
        }
    });

    for (int i = 0; i < 150000; ++i) {
        generate_random_car_files("data");
        std::this_thread::sleep_for(std::chrono::nanoseconds(50));
    }

    producer.join();
    consumer.join();
    return 0;
}

