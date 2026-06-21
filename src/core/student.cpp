#include "student.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Student::Student(long long id, const string& fullName, int academicYear) {
    setId(id);
    setFullName(fullName);
    setAcademicYear(academicYear);
}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
long long Student::getId() const {
    return id;
}

string Student::getFullName() const {
    return fullName;
}

int Student::getAcademicYear() const {
    return academicYear;
}

// ─────────────────────────────────────────────
// Setters
// ─────────────────────────────────────────────
void Student::setId(long long id) {
    if (id <= 0)
        throw std::invalid_argument("Student ID must be a positive number!");
    this->id = id;
}

void Student::setFullName(const string& fullName) {
    if (fullName.empty())
        throw std::invalid_argument("Student name cannot be empty!");
    if (fullName.length() < 3)
        throw std::invalid_argument("Student name is too short!");
    this->fullName = fullName;
}

void Student::setAcademicYear(int academicYear) {
    if (academicYear < 1 || academicYear > 5)
        throw std::invalid_argument("Academic year must be between 1 and 5!");
    this->academicYear = academicYear;
}

// ─────────────────────────────────────────────
void Student::displayInfo() const {
    if (fullName.empty())
        throw std::runtime_error("Student has no name set!");

    cout << "ID            : " << id           << "\n";
    cout << "Full Name     : " << fullName     << "\n";
    cout << "Academic Year : " << academicYear << "\n";
}