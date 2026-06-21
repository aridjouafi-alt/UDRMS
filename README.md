# UDRMS — University Dormitory & Restaurant Management System

A desktop application to manage student housing and restaurant services built with **Qt 6** and **C++**.

---

## What it does

- Add, remove, and find students in dormitory rooms
- Manage dormitories
- Manage restaurant menus and track meals served
- Data is saved automatically and loaded on next launch

---

## Built with

- C++17
- Qt 6 (Widgets)
- CMake

---

## How to run

1. Open **Qt Creator**
2. Open the `CMakeLists.txt` file
3. Click **Configure Project**
4. Press **Ctrl+R** to build and run

> Make sure the folder `src/data/` exists in the project directory before the first run.

---

## Note

Update the data file path in `studentwidget.cpp`, `dormitorywidget.cpp`, `restaurantwidget.cpp`, and `udrms.cpp` to match your machine:

```cpp
FileManager fileManager("C:/Your/Path/To/UDRMS/src/data/university.txt");
```
