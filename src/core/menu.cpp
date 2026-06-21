#include "menu.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
Menu::Menu(const vector<string>& breakfast,
           const vector<string>& lunch,
           const vector<string>& dinner)
    : breakfast(breakfast),
      lunch(lunch),
      dinner(dinner),
      mealsServed(0)
{
    if (breakfast.empty() && lunch.empty() && dinner.empty()) {
        throw invalid_argument("Menu cannot be completely empty");
    }

    auto validate = [](const vector<string>& v, const string& name) {
        for (const auto& item : v) {
            if (item.empty()) {
                throw invalid_argument(name + " contains empty meal item");
            }
        }
    };

    validate(breakfast, "Breakfast");
    validate(lunch, "Lunch");
    validate(dinner, "Dinner");
}

// ─────────────────────────────────────────────
// Getters
// ─────────────────────────────────────────────
const vector<string>& Menu::getBreakfast() const {
    return breakfast;
}

const vector<string>& Menu::getLunch() const {
    return lunch;
}

const vector<string>& Menu::getDinner() const {
    return dinner;
}

int Menu::getMealsServed() const {
    return mealsServed;
}

// ─────────────────────────────────────────────
// Setters
// ─────────────────────────────────────────────
void Menu::setBreakfast(const vector<string>& breakfast) {
    for (const auto& item : breakfast) {
        if (item.empty()) {
            throw invalid_argument("Breakfast contains empty meal item");
        }
    }
    this->breakfast = breakfast;
}

void Menu::setLunch(const vector<string>& lunch) {
    for (const auto& item : lunch) {
        if (item.empty()) {
            throw invalid_argument("Lunch contains empty meal item");
        }
    }
    this->lunch = lunch;
}

void Menu::setDinner(const vector<string>& dinner) {
    for (const auto& item : dinner) {
        if (item.empty()) {
            throw invalid_argument("Dinner contains empty meal item");
        }
    }
    this->dinner = dinner;
}

void Menu::setMealServed(int mealsServed) {
    if (mealsServed < 0) {
        throw invalid_argument("Meals served cannot be negative");
    }
    this->mealsServed = mealsServed;
}

// ─────────────────────────────────────────────
// Logic
// ─────────────────────────────────────────────
void Menu::updateMeal() {
    ++mealsServed;
}

// ─────────────────────────────────────────────
// Display
// ─────────────────────────────────────────────
void Menu::displayMenu() const {
    cout << "-- Breakfast --\n";
    for (const string& item : breakfast)
        cout << item << "\n";

    cout << "-- Lunch --\n";
    for (const string& item : lunch)
        cout << item << "\n";

    cout << "-- Dinner --\n";
    for (const string& item : dinner)
        cout << item << "\n";

    cout << "Meals Served : " << mealsServed << "\n";
}