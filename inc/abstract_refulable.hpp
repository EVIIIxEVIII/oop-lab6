#pragma once
#include <string>

class IRefuelable {
public:
    virtual void refuel(std::string carId) = 0;
    virtual ~IRefuelable() = default;
};
