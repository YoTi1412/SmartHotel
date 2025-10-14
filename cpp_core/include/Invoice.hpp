#pragma once
#include "Includes.hpp"
#include "Booking.hpp"
#include "Service.hpp"

class Invoice {
private:
    int id;
    int bookingId;
    double roomCharges;
    double serviceCharges;
    double taxRate = 0.10;
public:
    Invoice(int id, int bid, double roomCh, double servCh) : id(id), bookingId(bid), roomCharges(roomCh), serviceCharges(servCh) {}
    double getTotal() const { return (roomCharges + serviceCharges) * (1 + taxRate); }
};
