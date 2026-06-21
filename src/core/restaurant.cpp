#include "restaurant.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Restaurant::Restaurant(int id, const string& name, const Menu& menu)
    : id(id), name(name), menu(menu)
{
    if (id <= 0) {
        throw invalid_argument("Restaurant ID must be positive");
    }

    if (name.empty()) {
        throw invalid_argument("Restaurant name cannot be empty");
    }
}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
string Restaurant::getName() const {
    return name;
}

int Restaurant::getId() const {
    return id;
}

const Menu& Restaurant::getMenu() const {
    return menu;
}

// ─────────────────────────────────────────────
// Setters
// ─────────────────────────────────────────────
void Restaurant::setName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Restaurant name cannot be empty");
    }
    this->name = name;
}

void Restaurant::setId(int id) {
    if (id <= 0) {
        throw invalid_argument("Restaurant ID must be positive");
    }
    this->id = id;
}

void Restaurant::setMenu(const Menu& menu) {
    this->menu = menu;
}

// ─────────────────────────────────────────────
void Restaurant::viewMenu() const {
    cout << "Restaurant : " << name << "\n";
    menu.displayMenu();
}
void Restaurant::serveMeal() {
    menu.updateMeal();
}