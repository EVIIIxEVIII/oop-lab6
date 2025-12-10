#pragma once

#include <string>
#include "json.hpp"

enum class Type {
    Gas,
    Electric
};

class Car {
public:
    Car(std::string id, bool needsDining, bool needsRefuel, Type t)
        : id_(std::move(id)),
          needsDinning_(needsDining),
          needsRefuel_(needsRefuel),
          carType_(t)
    {}

    Car() = default;

    bool needsRefuel() const { return needsRefuel_; }
    bool needsDinning() const { return needsDinning_; }
    std::string getId() const { return id_; }
    Type getType() const { return carType_; }

    static Car parseCarFromJson(const nlohmann::json& j) {
        std::string id       = j.at("id").get<std::string>();
        bool needsDining     = j.at("needsDining").get<bool>();
        bool needsRefuel     = j.at("needsRefuel").get<bool>();
        std::string typeStr  = j.at("type").get<std::string>();

        Type t;
        if (typeStr == "gas")      t = Type::Gas;
        else if (typeStr == "electric") t = Type::Electric;
        else throw std::runtime_error("Invalid type in JSON");

        return Car(id, needsDining, needsRefuel, t);
    }

private:
    std::string id_;
    bool needsDinning_;
    bool needsRefuel_;
    Type carType_;
};

