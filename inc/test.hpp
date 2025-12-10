
#include "car_semaphore.hpp"
#include "electric_station.hpp"
#include "queue_queue.hpp"
#include "car_station.hpp"
#include "people_dinner.hpp"
#include "spsc_queue.hpp"
#include "gas_station.hpp"
#include <iostream>

inline void test() {
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

    Car c1("A", true, true, Type::Gas);
    Car c2("B", false, true, Type::Electric);
    Car c3("C", true, false, Type::Gas);
    Car c4("D", false, false, Type::Electric);

    router.routeCar(c1);
    router.routeCar(c2);
    router.routeCar(c3);
    router.routeCar(c4);

    gasStationForPeople.serveCars();
    electricStationForPeople.serveCars();

    SPSCQueue<Car> shared_queue;

    shared_queue.try_push(std::move(c1));
    shared_queue.try_push(std::move(c2));

    Car c1_poped;
    Car c2_poped;

    shared_queue.try_pop(c1_poped);
    shared_queue.try_pop(c2_poped);

    std::cout << c1_poped.getId() << '\n';
    std::cout << c2_poped.getId() << '\n';

    std::cout << sizeof(Car) << '\n';
    std::cout << alignof(Car) << '\n';

    std::cout << "Done routing and serving.\n";
}
