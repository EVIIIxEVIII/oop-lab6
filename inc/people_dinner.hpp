#pragma once

#include "abstract_dineable.hpp"
#include <iostream>

class PeopleDinner : public IDineable {
public:
    void serveDinner(std::string carId) override {
        std::cout << "Feeding people in car " << carId << '\n';
    };
};
