#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
#include "dormitory.h"
 
class University {
private:
    std::string name;
    std::string location;
    std::string address;
    std::vector<Dormitory> dormitories;
 
public:
    // Constructors
    University();
    University(const std::string& name,
               const std::string& location,
               const std::string& address);
 
    // ── Getters ──────────────────────────────────────────────
    std::string getName()     const ;
    std::string getLocation() const ;
    std::string getAddress()  const ;
 
    const std::vector<Dormitory>& getDormitories() const ;
 
    // ── Setters ──────────────────────────────────────────────
    void setName    (const std::string& name)     ;
    void setLocation(const std::string& location) ;
    void setAddress (const std::string& address)  ;
 
    void setDormitories(const std::vector<Dormitory>& dormitories) ;
 
    // ── Methods ──────────────────────────────────────────────
    void addDormitory   (const Dormitory& dormitory);
    void removeDormitory(const std::string& name);
    void displayInfo    () const;
};

#endif