#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    long long id;
    std::string fullName;
    int academicYear;

public:
    // Constructor
    Student(long long id, const std::string& fullName, int academicYear);

    // Getters
    long long   getId()           const;
    std::string getFullName()     const;
    int         getAcademicYear() const;

    // Setters
    void setId          (long long id);
    void setFullName    (const std::string& fullName);
    void setAcademicYear(int academicYear);

    // Method from UML
    void displayInfo() const;
};

#endif