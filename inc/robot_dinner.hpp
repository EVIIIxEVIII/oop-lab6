#pragma once

#include "abstract_dineable.hpp"
#include <iostream>

class RobotDinner : public IDineable {
public:
    void serveDinner(std::string carId) override {
        std::cout << "Feeding robots in car " << carId << '\n';
    };
};
