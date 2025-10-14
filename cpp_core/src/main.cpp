#include <iostream>
#include <limits>
#include <iomanip>
#include "BookingManager.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void printHeader() {
    clearScreen();
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              🏨 SMART HOTEL MANAGEMENT 🏨             ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

bool authenticate() {
    std::string password;
    std::cout << "🔐 Enter admin password: ";
    std::getline(std::cin, password);
    std::cout << std::endl;
    if (password == "admin123") {
        Logger::info("✅ Access granted!");
        return true;
    }
    Logger::error("❌ Access denied!");
    return false;
}

void displayMenu() {
    printHeader();
    std::cout << "📋 MAIN MENU" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "1️⃣  Add New Booking" << std::endl;
    std::cout << "2️⃣  Search Booking" << std::endl;
    std::cout << "3️⃣  Update Booking" << std::endl;
    std::cout << "4️⃣  Cancel Booking" << std::endl;
    std::cout << "5️⃣  View All Bookings" << std::endl;
    std::cout << "6️⃣  Exit System" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "🎯 Enter your choice (1-6): ";
}

std::string getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int getIntInput(const std::string& prompt, bool allowExit = true) {
    while (true) {
        std::string input = getInput(prompt);
        if (allowExit && input == "exit") return -1;
        try {
            return std::stoi(input);
        } catch (...) {
            Logger::error("❌ Please enter a valid number!");
        }
    }
}

bool confirmAction(const std::string& action) {
    std::cout << std::endl << "⚠️  " << action << std::endl;
    std::cout << "Are you sure? (y/n): ";
    std::string response;
    std::getline(std::cin, response);
    return response == "y" || response == "Y" || response == "yes" || response == "YES";
}

void pause() {
    std::cout << "\n⏸️  Press Enter to continue...";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Logger::info("🚀 SmartHotel System Starting...");
    if (!authenticate()) return 1;

    BookingManager manager;
    printHeader();

    while (true) {
        displayMenu();
        std::string choiceStr = getInput("");
        try {
            int choice = std::stoi(choiceStr);

            switch (choice) {
                case 1: { // Add Booking
                    printHeader();
                    std::cout << "➕ CREATE NEW BOOKING" << std::endl;
                    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;

                    int id = getIntInput("🆔 Booking ID: ");
                    if (id == -1) break;

                    std::string name = getInput("👤 Customer Name: ");
                    if (name == "exit") break;
                    if (name.empty()) {
                        Logger::error("❌ Name cannot be empty!");
                        pause(); break;
                    }

                    int room = getIntInput("🛏️  Room Number (1=Single, 2=Double): ");
                    if (room == -1) break;
                    if (room != 1 && room != 2) {
                        Logger::error("❌ Invalid room number!");
                        pause(); break;
                    }

                    std::string checkIn = getInput("📅 Check-In Date (YYYY-MM-DD): ");
                    if (checkIn == "exit") break;

                    std::string checkOut = getInput("📤 Check-Out Date (YYYY-MM-DD): ");
                    if (checkOut == "exit") break;

                    try {
                        Booking booking(id, name, room, checkIn, checkOut);
                        manager.addBooking(booking);
                        std::cout << "\n🎉 Booking created successfully!" << std::endl;
                        pause();
                    } catch (const std::exception& e) {
                        Logger::error(e.what());
                        pause();
                    }
                    break;
                }

                case 2: { // Search
                    printHeader();
                    std::cout << "🔍 SEARCH BOOKING" << std::endl;
                    int id = getIntInput("🆔 Enter Booking ID: ");
                    if (id == -1) break;
                    manager.searchBooking(id);
                    pause();
                    break;
                }

                case 3: { // Update
                    printHeader();
                    std::cout << "✏️  UPDATE BOOKING" << std::endl;
                    int id = getIntInput("🆔 Enter Booking ID: ");
                    if (id == -1) break;

                    std::string checkIn = getInput("📅 New Check-In Date (YYYY-MM-DD): ");
                    if (checkIn == "exit") break;
                    std::string checkOut = getInput("📤 New Check-Out Date (YYYY-MM-DD): ");
                    if (checkOut == "exit") break;

                    try {
                        manager.updateBooking(id, checkIn, checkOut);
                        std::cout << "\n✅ Booking updated successfully!" << std::endl;
                    } catch (const std::exception& e) {
                        Logger::error(e.what());
                    }
                    pause();
                    break;
                }

                case 4: { // Delete
                    printHeader();
                    std::cout << "🗑️  CANCEL BOOKING" << std::endl;
                    int id = getIntInput("🆔 Enter Booking ID to cancel: ");
                    if (id == -1) break;

                    if (confirmAction("Cancel booking ID " + std::to_string(id))) {
                        manager.deleteBooking(id);
                        std::cout << "\n✅ Booking cancelled!" << std::endl;
                    } else {
                        std::cout << "\n❌ Cancelled operation." << std::endl;
                    }
                    pause();
                    break;
                }

                case 5: { // List
                    printHeader();
                    std::cout << "📋 ALL BOOKINGS" << std::endl;
                    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
                    manager.listBookings();
                    pause();
                    break;
                }

                case 6:
                    printHeader();
                    Logger::info("👋 Thank you for using SmartHotel!");
                    return 0;

                default:
                    Logger::warning("❌ Invalid choice! Please select 1-6.");
                    pause();
            }
        } catch (...) {
            Logger::warning("❌ Invalid choice! Please enter a number 1-6.");
            pause();
        }
    }
    return 0;
}
