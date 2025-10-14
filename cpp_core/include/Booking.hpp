#pragma once
#include "Includes.hpp"
#include "Utils.hpp"

class Booking {
private:
    int id;
    std::string customerName;
    int roomNumber;
    time_t checkIn;
    time_t checkOut;
    std::string status;

    bool isValidDate(const std::string& dateStr) const {
        if (dateStr.length() != 10) return false;
        struct tm tm = {};
        if (std::sscanf(dateStr.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) != 3) {
            return false;
        }
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_hour = 12; // Use noon to avoid timezone issues
        tm.tm_min = 0;
        tm.tm_sec = 0;
        tm.tm_isdst = -1;
        time_t t = mktime(&tm);
        return t != -1;
    }

public:
    Booking(int id, std::string name, int room, std::string checkInStr, std::string checkOutStr)
        : id(id), customerName(name), roomNumber(room), status("confirmed") {

        if (!isValidDate(checkInStr) || !isValidDate(checkOutStr)) {
            throw std::invalid_argument("Invalid date format. Use YYYY-MM-DD");
        }

        struct tm tmIn = {}, tmOut = {};
        std::istringstream ssIn(checkInStr), ssOut(checkOutStr);
        ssIn >> std::get_time(&tmIn, "%Y-%m-%d");
        ssOut >> std::get_time(&tmOut, "%Y-%m-%d");

        tmIn.tm_hour = 14; // Check-in at 2 PM
        tmOut.tm_hour = 12; // Check-out at 12 PM
        tmIn.tm_min = tmIn.tm_sec = tmOut.tm_min = tmOut.tm_sec = 0;
        tmIn.tm_isdst = tmOut.tm_isdst = -1;

        checkIn = mktime(&tmIn);
        checkOut = mktime(&tmOut);

        if (checkIn == -1 || checkOut == -1 || checkIn >= checkOut) {
            throw std::invalid_argument("Invalid dates: Check-out must be after check-in");
        }
    }

    // Getters (unchanged)
    int getId() const { return id; }
    int getRoomNumber() const { return roomNumber; }
    time_t getCheckIn() const { return checkIn; }
    time_t getCheckOut() const { return checkOut; }
    std::string getCustomerName() const { return customerName; }
    std::string getStatus() const { return status; }

    void setStatus(const std::string& s) { status = s; }

    std::string toString() const {
        char bufIn[32], bufOut[32];
        std::strftime(bufIn, sizeof(bufIn), "%Y-%m-%d %H:%M", localtime(&checkIn));
        std::strftime(bufOut, sizeof(bufOut), "%Y-%m-%d %H:%M", localtime(&checkOut));
        return "ID=" + Utils::intToString(id) + ", Name=" + customerName +
               ", Room=" + Utils::intToString(roomNumber) +
               ", CheckIn=" + std::string(bufIn) +
               ", CheckOut=" + std::string(bufOut) +
               ", Status=" + status;
    }
};
