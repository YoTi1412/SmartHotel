#pragma once
#include "Includes.hpp"

class Guest {
private:
    int id;
    std::string name;
    std::string contact;
public:
    Guest(int id, std::string name, std::string contact)
        : id(id), name(name), contact(contact) {}
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }
};
