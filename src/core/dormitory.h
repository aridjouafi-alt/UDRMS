#ifndef DORMITORY_H
#define DORMITORY_H

#include <string>
#include <vector>
#include "room.h"
#include "restaurant.h"
 
class Dormitory {
private:
    std::string name;
    int capacity;
    int totalRooms;
    std::vector<Room> rooms;
    Restaurant restaurant;

public:
    // Constructor
    Dormitory(const std::string& name, int capacity, int totalRooms, const Restaurant& restaurant);
 
    // Getters
    std::string getName() const;
    int getCapacity() const;
    int getTotalRooms() const;

    const std::vector<Room>& getRooms() const;
    const Restaurant& getRestaurant() const;
 
    // Setters
    void setName(const std::string& name);
    void setCapacity(int capacity);
    void setTotalRooms(int totalRooms);

    void setRooms(const std::vector<Room>& rooms) ;
    void setRestaurant(const Restaurant& restaurant) ;
 
    // Methods from UML
    void display() const;
    void assignStudentToRoom(const Student& student, int roomNumber);
    void removeStudent(const Student& student);
};
#endif