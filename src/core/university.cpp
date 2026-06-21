#include "University.h"
#include "dormitory.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructors
University::University() : name("unknown"), location("unknown"), address("unknown") {}

University::University(const string& name,
                       const string& location,
                       const string& address)
    : name(name), location(location), address(address) {}

// Getters
string University::getName()     const { return name; }
string University::getLocation() const { return location; }
string University::getAddress()  const { return address; }

const vector<Dormitory>& University::getDormitories() const { return dormitories; }

// Setters
void University::setName(const string& name) {
    if (name.empty())
        throw std::invalid_argument("University name cannot be empty!");
    this->name = name;
}

void University::setLocation(const string& location) {
    if (location.empty())
        throw std::invalid_argument("Location cannot be empty!");
    this->location = location;
}

void University::setAddress(const string& address) {
    if (address.empty())
        throw std::invalid_argument("Address cannot be empty!");
    this->address = address;
}

void University::setDormitories(const vector<Dormitory>& dormitories) {
    this->dormitories = dormitories;
}

// Methods
void University::addDormitory(const Dormitory& dormitory) {
    for (const Dormitory& d : dormitories) {
        if (d.getName() == dormitory.getName())
            throw std::runtime_error("Dormitory '" + dormitory.getName() + "' already exists!");
    }
    dormitories.push_back(dormitory);
}

void University::removeDormitory(const string& name) {
    if (name.empty())
        throw std::invalid_argument("Dormitory name cannot be empty!");

    for (vector<Dormitory>::iterator i = dormitories.begin(); i != dormitories.end(); ++i) {
        if (i->getName() == name) {
            dormitories.erase(i);
            return;
        }
    }
    // not found → throw instead of cout
    throw std::runtime_error("Dormitory '" + name + "' not found!");
}

void University::displayInfo() const {
    if (dormitories.empty())
        throw std::runtime_error("No dormitories registered in the university!");

    cout << "University:  " << name               << endl;
    cout << "Location:    " << location           << endl;
    cout << "Address:     " << address            << endl;
    cout << "Dormitories: " << dormitories.size() << endl;
    for (const Dormitory& d : dormitories) {
        cout << "  - " << d.getName() << endl;
    }
}