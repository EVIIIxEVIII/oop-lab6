#pragma once
#include "abstract_refulable.hpp"
#include <iostream>

class GasStation : public IRefuelable {

public:
    void refuel(std::string carId) override {
        std::cout << "Refueling gas car " << carId << '\n';
    };
};

