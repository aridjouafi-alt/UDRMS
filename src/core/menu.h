#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
private:
    std::vector<std::string> breakfast;
    std::vector<std::string> lunch;
    std::vector<std::string> dinner;
    int mealsServed;

public:
    // Constructor
    Menu(const std::vector<std::string>& breakfast,
         const std::vector<std::string>& lunch,
         const std::vector<std::string>& dinner);

    // Getters
    const std::vector<std::string>& getBreakfast() const;
    const std::vector<std::string>& getLunch()     const;
    const std::vector<std::string>& getDinner()    const;
    int getMealsServed()                           const;

    // Setters
    void setBreakfast(const std::vector<std::string>& breakfast);
    void setLunch    (const std::vector<std::string>& lunch);
    void setDinner   (const std::vector<std::string>& dinner);

    void setMealServed (int mealsServed) ;
    // Methods from UML
    void updateMeal();
    void displayMenu() const;
};

#endif