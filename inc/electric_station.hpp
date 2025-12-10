#pragma once
#include "abstract_refulable.hpp"
#include <iostream>

class ElectricStation : public IRefuelable {

public:
    void refuel(std::string carId) override {
        std::cout << "Refueling electric car " << carId << '\n';
    };
};

