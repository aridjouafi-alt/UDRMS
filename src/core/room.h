#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "student.h"

class Room {
private:
    int roomNumber;
    int capacity;
    std::vector<Student> occupants;
 
public:
    // Constructor
    Room(int roomNumber, int capacity);
 
    // Getters
    int getRoomNumber() const;
    int getCapacity()   const;

    const std::vector<Student>& getOccupants() const;
 
    // Setters
    void setRoomNumber(int roomNumber);
    void setCapacity  (int capacity);
 
    void setOccupants (const std::vector<Student>& occupants);
    // Methods from UML
    bool isAvailable() const;
    void display()     const;
};

#endif