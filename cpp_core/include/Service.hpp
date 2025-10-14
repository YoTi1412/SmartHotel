#pragma once
#include "Includes.hpp"

class Service {
private:
    int id;
    int bookingId;
    std::string type;
    double cost;
    int quantity;
public:
    Service(int id, int bid, std::string type, double cost, int qty) : id(id), bookingId(bid), type(type), cost(cost), quantity(qty) {}
    double getTotal() const { return cost * quantity; }
};
