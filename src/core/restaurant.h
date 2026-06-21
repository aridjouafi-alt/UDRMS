#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "menu.h"

class Restaurant {
private:
    int id;
    std::string name;
    Menu menu;

public:
    // Constructor
    Restaurant(int id, const std::string& name, const Menu& menu);

    // Getters
    std::string getName()         const;
    int         getId()           const;
    const Menu& getMenu()         const;

    // Setters
    void setName        (const std::string& name);
    void setId          (int id);
    void setMenu        (const Menu& menu);

    // Methods from UML
    void viewMenu()  const;
    void serveMeal();
};

#endif