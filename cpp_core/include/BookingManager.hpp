#pragma once
#include "Includes.hpp"
#include "Booking.hpp"
#include "Room.hpp"
#include "Guest.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

class BookingManager {
private:
    std::vector<Room> rooms;
    std::vector<Guest> guests;
    std::vector<Booking> bookings;
    void saveToFile();
    bool isRoomAvailable(int roomId, time_t checkIn, time_t checkOut);
public:
    BookingManager();
    void addBooking(const Booking& booking);
    void searchBooking(int id);
    void updateBooking(int id, std::string checkIn, std::string checkOut);
    void deleteBooking(int id);
    void listBookings();
};
