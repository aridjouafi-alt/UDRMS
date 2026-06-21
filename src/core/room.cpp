#include "room.h"
#include "student.h"
#include <iostream>
#include <stdexcept>  // ← add this

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Room::Room(int roomNumber, int capacity) {
    setRoomNumber(roomNumber);
    setCapacity(capacity);
}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
int Room::getRoomNumber() const {
    return roomNumber;
}

int Room::getCapacity() const {
    return capacity;
}

const vector<Student>& Room::getOccupants() const {
    return occupants;
}

// ─────────────────────────────────────────────
// Setters
// ─────────────────────────────────────────────
void Room::setRoomNumber(int roomNumber) {
    if (roomNumber <= 0)
        throw std::invalid_argument("Room number must be a positive number!");
    this->roomNumber = roomNumber;
}

void Room::setCapacity(int capacity) {
    if (capacity <= 0)
        throw std::invalid_argument("Room capacity must be a positive number!");
    if (capacity > 6)
        throw std::invalid_argument("Room capacity cannot exceed 6 students!");
    this->capacity = capacity;
}

void Room::setOccupants(const vector<Student>& occupants) {
    if ((int)occupants.size() > capacity)
        throw std::runtime_error("Number of occupants exceeds room capacity!");
    this->occupants = occupants;
}

// ─────────────────────────────────────────────
bool Room::isAvailable() const {
    return occupants.size() < (size_t)capacity;
}

// ─────────────────────────────────────────────
void Room::display() const {
    cout << "Room Number : " << roomNumber          << "\n";
    cout << "Capacity    : " << capacity            << "\n";
    cout << "Occupants   : " << occupants.size() << "/" << capacity << "\n";
    for (const Student& student : occupants) {
        student.displayInfo();
    }
}