#pragma once

#include "car_station.hpp"

class CarSemaphore {
public:
    CarSemaphore(CarStation& gas, CarStation& electric)
        : gas_(gas), electric_(electric) {}

    void routeCar(Car& car) {
        if (car.getType() == Type::Gas) gas_.addCar(car);
        if (car.getType() == Type::Electric) electric_.addCar(car);

        gas_.serveCars();
        electric_.serveCars();
    }

private:
    CarStation& gas_;
    CarStation& electric_;
};
