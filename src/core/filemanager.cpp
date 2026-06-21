#include "filemanager.h"
#include <iostream>
#include <sstream>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
FileManager::FileManager(const string& filename)
    : filename(filename) {}

// ═════════════════════════════════════════════
// SAVE HELPERS (private)
// ═════════════════════════════════════════════

void FileManager::saveStudent(ofstream& out, const Student& s) const {
    out << s.getId()           << "\n";
    out << s.getFullName()     << "\n";
    out << s.getAcademicYear() << "\n";
}

void FileManager::saveMenu(ofstream& out, const Menu& m) const {
    out << m.getBreakfast().size() << "\n";
    for (const string& item : m.getBreakfast())
        out << item << "\n";

    out << m.getLunch().size() << "\n";
    for (const string& item : m.getLunch())
        out << item << "\n";

    out << m.getDinner().size() << "\n";
    for (const string& item : m.getDinner())
        out << item << "\n";

    out << m.getMealsServed() << "\n";
}

void FileManager::saveRestaurant(ofstream& out, const Restaurant& r) const {
    out << r.getId()   << "\n";
    out << r.getName() << "\n";
    saveMenu(out, r.getMenu());
}

void FileManager::saveRoom(ofstream& out, const Room& r) const {
    out << r.getRoomNumber() << "\n";
    out << r.getCapacity()   << "\n";

    const vector<Student>& occupants = r.getOccupants();
    out << occupants.size()  << "\n";
    for (const Student& s : occupants)
        saveStudent(out, s);
}

void FileManager::saveDormitory(ofstream& out, const Dormitory& d) const {
    out << d.getName()       << "\n";
    out << d.getCapacity()   << "\n";
    out << d.getTotalRooms() << "\n";

    saveRestaurant(out, d.getRestaurant());

    // count and save ONLY occupied rooms
    const vector<Room>& rooms = d.getRooms();
    int occupiedCount = 0;
    for (const Room& r : rooms)
        if (!r.getOccupants().empty())
            occupiedCount++;

    out << occupiedCount << "\n";
    for (const Room& r : rooms)
        if (!r.getOccupants().empty())
            saveRoom(out, r);
}

// ═════════════════════════════════════════════
// LOAD HELPERS (private)
// ═════════════════════════════════════════════

Student FileManager::loadStudent(ifstream& in) const {
    long long id;
    int       academicYear;
    string    fullName;

    in >> id;          // reads long long correctly
    in.ignore();
    getline(in, fullName);
    in >> academicYear;
    in.ignore();

    return Student(id, fullName, academicYear);
}
Menu FileManager::loadMenu(ifstream& in) const {
    vector<string> breakfast, lunch, dinner;
    int count, mealsServed;
    string item;

    in >> count; in.ignore();
    for (int i = 0; i < count; i++) {
        getline(in, item);
        breakfast.push_back(item);
    }

    in >> count; in.ignore();
    for (int i = 0; i < count; i++) {
        getline(in, item);
        lunch.push_back(item);
    }

    in >> count; in.ignore();
    for (int i = 0; i < count; i++) {
        getline(in, item);
        dinner.push_back(item);
    }

    in >> mealsServed;
    in.ignore();

    Menu m(breakfast, lunch, dinner);
    for (int i = 0; i < mealsServed; i++)
        m.updateMeal();

    return m;
}

Restaurant FileManager::loadRestaurant(ifstream& in) const {
    int    restaurantID;
    string name;

    in >> restaurantID;
    in.ignore();
    getline(in, name);

    Menu menu = loadMenu(in);
    return Restaurant(restaurantID, name, menu);
}

Room FileManager::loadRoom(ifstream& in) const {
    int roomNumber, capacity, occupantCount;

    in >> roomNumber >> capacity >> occupantCount;
    in.ignore();

    Room room(roomNumber, capacity);

    vector<Student> occupants;
    for (int i = 0; i < occupantCount; i++)
        occupants.push_back(loadStudent(in));

    room.setOccupants(occupants);
    return room;
}

Dormitory FileManager::loadDormitory(ifstream& in) const {
    string name;
    int capacity, totalRooms, occupiedCount;

    getline(in, name);
    in >> capacity >> totalRooms;
    in.ignore();

    Restaurant restaurant = loadRestaurant(in);
    Dormitory dorm(name, capacity, totalRooms, restaurant);

    in >> occupiedCount;
    in.ignore();

    // load only occupied rooms from file
    vector<Room> occupiedRooms;
    for (int i = 0; i < occupiedCount; i++)
        occupiedRooms.push_back(loadRoom(in));

    // restore all 1000 rooms
    vector<Room> allRooms;
    for (int i = 1; i <= 1000; i++)
        allRooms.push_back(Room(i, 1));

    // place students back into correct rooms by room number
    for (const Room& loaded : occupiedRooms) {
        for (Room& r : allRooms) {
            if (r.getRoomNumber() == loaded.getRoomNumber()) {
                r.setOccupants(loaded.getOccupants());
                break;
            }
        }
    }

    dorm.setRooms(allRooms);
    return dorm;
}

// ═════════════════════════════════════════════
// PUBLIC INTERFACE
// ═════════════════════════════════════════════

void FileManager::saveUniversity(const University& university) const {
    ofstream out(filename);
    if (!out.is_open())
        throw runtime_error("Error: Could not open file for saving: " + filename);

    out << university.getName()     << "\n";
    out << university.getLocation() << "\n";
    out << university.getAddress()  << "\n";

    const vector<Dormitory>& dormitories = university.getDormitories();
    out << dormitories.size() << "\n";
    for (const Dormitory& d : dormitories)
        saveDormitory(out, d);

    out.close();
    cout << "University data saved to " << filename << "\n";
}

University FileManager::loadUniversity() const {
    ifstream in(filename);
    if (!in.is_open())
        throw runtime_error("Error: Could not open file for loading: " + filename);

    string name, location, address;
    int dormCount;

    getline(in, name);
    getline(in, location);
    getline(in, address);

    University university(name, location, address);

    in >> dormCount;
    in.ignore();
    for (int i = 0; i < dormCount; i++)
        university.addDormitory(loadDormitory(in));

    in.close();
    cout << "University data loaded from " << filename << "\n";
    return university;
}