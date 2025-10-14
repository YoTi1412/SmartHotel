#include "BookingManager.hpp"
#include <fstream>

BookingManager::BookingManager() {
    // Initialize sample rooms and guests
    rooms.emplace_back(1, "Single", 100.0);
    rooms.emplace_back(2, "Double", 150.0);
    guests.emplace_back(1, "John Doe", "john@example.com");
    Logger::info("BookingManager initialized with sample data.");
}

void BookingManager::saveToFile() {
    std::ofstream file("bookings.csv");
    if (!file.is_open()) {
        Logger::error("Failed to open bookings.csv");
        return;
    }
    for (const auto& b : bookings) {
        file << b.getId() << "," << b.getCustomerName() << "," << b.getRoomNumber() << ","
             << Utils::formatTime(b.getCheckIn()) << "," << Utils::formatTime(b.getCheckOut()) << ","
             << b.getStatus() << "\n";
    }
    file.close();
    Logger::info("Bookings saved to bookings.csv");
}

bool BookingManager::isRoomAvailable(int roomId, time_t checkIn, time_t checkOut) {
    for (const auto& b : bookings) {
        if (b.getRoomNumber() == roomId && b.getStatus() == "confirmed") {
            if (!(checkOut <= b.getCheckIn() || checkIn >= b.getCheckOut())) {
                return false;
            }
        }
    }
    return true;
}

void BookingManager::addBooking(const Booking& booking) {
    if (!isRoomAvailable(booking.getRoomNumber(), booking.getCheckIn(), booking.getCheckOut())) {
        Logger::error("Room " + Utils::intToString(booking.getRoomNumber()) + " is not available for the selected dates.");
        return;
    }
    for (auto& room : rooms) {
        if (room.getId() == booking.getRoomNumber()) {
            room.setStatus("occupied");
            break;
        }
    }
    bookings.push_back(booking);
    saveToFile();
    Logger::info("Booking added: " + booking.toString());
}

void BookingManager::searchBooking(int id) {
    for (const auto& b : bookings) {
        if (b.getId() == id) {
            Logger::info("Found booking: " + b.toString());
            return;
        }
    }
    Logger::warning("Booking ID " + Utils::intToString(id) + " not found.");
}

void BookingManager::updateBooking(int id, std::string checkIn, std::string checkOut) {
    for (auto& b : bookings) {
        if (b.getId() == id && b.getStatus() == "confirmed") {
            try {
                Booking temp(b.getId(), b.getCustomerName(), b.getRoomNumber(), checkIn, checkOut);
                if (isRoomAvailable(b.getRoomNumber(), temp.getCheckIn(), temp.getCheckOut())) {
                    b = temp;
                    saveToFile();
                    Logger::info("Booking updated: " + b.toString());
                    return;
                } else {
                    Logger::error("Cannot update: Room not available for new dates.");
                }
            } catch (const std::exception& e) {
                Logger::error(e);
            }
            return;
        }
    }
    Logger::warning("Booking ID " + Utils::intToString(id) + " not found or cancelled.");
}

void BookingManager::deleteBooking(int id) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->getId() == id) {
            it->setStatus("cancelled");
            for (auto& room : rooms) {
                if (room.getId() == it->getRoomNumber()) {
                    room.setStatus("available");
                    break;
                }
            }
            saveToFile();
            Logger::info("Booking ID " + Utils::intToString(id) + " cancelled.");
            return;
        }
    }
    Logger::warning("Booking ID " + Utils::intToString(id) + " not found.");
}

void BookingManager::listBookings() {
    if (bookings.empty()) {
        Logger::info("No bookings found.");
        return;
    }
    for (const auto& b : bookings) {
        Logger::info("Booking: " + b.toString());
    }
}
