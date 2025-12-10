#pragma once
#include <string>

class IDineable {
public:
    virtual void serveDinner(std::string carId) = 0;
    virtual ~IDineable() = default;
};
