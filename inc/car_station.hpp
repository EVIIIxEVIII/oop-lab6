#pragma once

#include "abstract_dineable.hpp"
#include "abstract_queue.hpp"
#include "abstract_refulable.hpp"
#include "car.hpp"

class CarStation {
public:
    CarStation(IDineable& dineable, IRefuelable& refuelable, IQueue<Car>& queue)
        : diningService_(dineable),
          refuelable_(refuelable),
          queue_(queue)
    {}

    void serveCars() {
        while (!queue_.empty()) {
            Car car;
            queue_.pop(car);
            if (car.needsDinning()) diningService_.serveDinner(car.getId());
            if (car.needsRefuel()) refuelable_.refuel(car.getId());
        }
    }

    void addCar(const Car& car) {
        queue_.push(car);
    }

private:
    IDineable& diningService_;
    IRefuelable& refuelable_;
    IQueue<Car>& queue_;
};

