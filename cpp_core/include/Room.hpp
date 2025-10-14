#pragma once
#include "Includes.hpp"

class Room {
private:
    int id;
    std::string type;
    double rate;
    std::string status;  // available, occupied, dirty
public:
    Room(int id, std::string type, double rate)
        : id(id), type(type), rate(rate), status("available") {}
    // Getters
    int getId() const { return id; }
    std::string getType() const { return type; }
    double getRate() const { return rate; }
    std::string getStatus() const { return status; }
    // Setters
    void setStatus(const std::string& s) { status = s; }
};
