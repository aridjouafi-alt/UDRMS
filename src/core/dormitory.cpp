#include "dormitory.h"
#include "student.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Dormitory::Dormitory(const string& name, int capacity,
                     int totalRooms, const Restaurant& restaurant)
    : name(name), capacity(capacity),
    totalRooms(totalRooms), restaurant(restaurant)
{
    if (name.empty())
        throw runtime_error("Dormitory name cannot be empty");

    if (capacity <= 0)
        throw runtime_error("Capacity must be greater than 0");

    if (totalRooms <= 0)
        throw runtime_error("Total rooms must be greater than 0");

}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
string Dormitory::getName() const { return name; }
int Dormitory::getCapacity() const { return capacity; }
int Dormitory::getTotalRooms() const { return totalRooms; }
const vector<Room>& Dormitory::getRooms() const { return rooms; }
const Restaurant& Dormitory::getRestaurant() const { return restaurant; }

// ─────────────────────────────────────────────
// Setters (with validation)
// ─────────────────────────────────────────────
void Dormitory::setName(const string& name) {
    if (name.empty())
        throw runtime_error("Dormitory name cannot be empty");

    this->name = name;
}

void Dormitory::setCapacity(int capacity) {
    if (capacity <= 0)
        throw runtime_error("Capacity must be greater than 0");

    this->capacity = capacity;
}

void Dormitory::setTotalRooms(int totalRooms) {
    if (totalRooms <= 0)
        throw runtime_error("Total rooms must be greater than 0");

    if (totalRooms < (int)rooms.size())
        throw runtime_error("Total rooms cannot be less than existing rooms");

    this->totalRooms = totalRooms;
}

void Dormitory::setRooms(const vector<Room>& rooms) {

    if ((int)rooms.size() > totalRooms)
        throw runtime_error("Number of rooms exceeds dormitory total rooms");

    this->rooms = rooms;
}

void Dormitory::setRestaurant(const Restaurant& restaurant) {
    this->restaurant = restaurant;
}

// ─────────────────────────────────────────────
// assignStudent()
// ─────────────────────────────────────────────
void Dormitory::assignStudentToRoom(const Student& student, int roomNumber) {
    if (rooms.empty())
        throw runtime_error("No rooms available in this dormitory");

    for (Room& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            if (!room.isAvailable())
                throw runtime_error("Room " + to_string(roomNumber) + " is already occupied");

            vector<Student> occupants = room.getOccupants();
            occupants.push_back(student);
            room.setOccupants(occupants);

            cout << "Student " << student.getFullName()
                 << " assigned to room " << roomNumber
                 << " in dormitory " << name << "\n";
            return;
        }
    }

    throw runtime_error("Room " + to_string(roomNumber) + " does not exist");
}

// ─────────────────────────────────────────────
// removeStudent()
// ─────────────────────────────────────────────
void Dormitory::removeStudent(const Student& student) {

    if (rooms.empty())
        throw runtime_error("Dormitory has no rooms");

    for (Room& room : rooms) {
        vector<Student> occupants = room.getOccupants();

        for (auto i = occupants.begin(); i != occupants.end(); ++i) {
            if (i->getId() == student.getId()) {
                occupants.erase(i);
                room.setOccupants(occupants);

                cout << "Student " << student.getFullName()
                     << " removed from room " << room.getRoomNumber()
                     << " in dormitory " << name << "\n";
                return;
            }
        }
    }

    throw runtime_error("Student " + student.getFullName() +
                        " not found in dormitory " + name);
}