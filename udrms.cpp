#include "udrms.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QTabWidget>
#include <QMessageBox>
#include <vector>
#include "studentwidget.h"
#include "dormitorywidget.h"
#include "restaurantwidget.h"
#include "filemanager.h"
#include "room.h"

using namespace std;

udrms::udrms(QWidget *parent)
    : QMainWindow(parent)
{
    FileManager fileManager("C:/Users/Rawnak/Documents/udrms/src/data/university.txt");

    // try to load existing data
    try {
        university = fileManager.loadUniversity();
    } catch (...) {
        university = University("ensia", "sidi abdellah", "algiers16086");
    }

    // if no dormitories exist, create defaults
    if (university.getDormitories().empty()) {
        Menu defaultMenu(
            {"Coffee", "Tea", "Milk", "Bread", "Butter", "Eggs", "Juice"},
            {"Water", "Salad"},
            {"Water", "Salad"}
            );

        // Mahelma 4
        Restaurant restaurant1(1, "Mahelma 4 Restaurant", defaultMenu);
        Dormitory dorm1("Mahelma 4", 1, 1000, restaurant1);
        university.addDormitory(dorm1);

        // Mahelma 3
        Restaurant restaurant2(2, "Mahelma 3 Restaurant", defaultMenu);
        Dormitory dorm2("Mahelma 3", 1, 1000, restaurant2);
        university.addDormitory(dorm2);

        // save immediately
        fileManager.saveUniversity(university);
    }

    // add 1000 rooms to every dormitory that needs them
    for (int d = 0; d < (int)university.getDormitories().size(); d++) {
        Dormitory *dorm = const_cast<Dormitory*>(&university.getDormitories()[d]);

        if (dorm->getRooms().size() < 1000) {
            vector<Room> rooms;

            // keep existing occupied rooms
            for (const Room &r : dorm->getRooms())
                if (!r.getOccupants().empty())
                    rooms.push_back(r);

            // track used room numbers
            vector<int> usedNumbers;
            for (const Room &r : rooms)
                usedNumbers.push_back(r.getRoomNumber());

            // fill up to 1000
            for (int i = 1; i <= 1000; i++) {
                bool exists = false;
                for (int n : usedNumbers)
                    if (n == i) { exists = true; break; }
                if (!exists)
                    rooms.push_back(Room(i, 1));
            }

            dorm->setRooms(rooms);
        }
    }

    // ── UI setup ─────────────────────────────────────────────
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Header
    QWidget *header = new QWidget();
    header->setFixedHeight(50);
    header->setStyleSheet("background-color:#E74C54;");

    QLabel *title = new QLabel("ENSIA — University Dormitory & Restaurant Management System");
    title->setStyleSheet("color:white; font-size:16px; font-weight:500;");

    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->addWidget(title);
    headerLayout->setContentsMargins(20, 0, 0, 0);

    // Tabs
    tabs = new QTabWidget();
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabs->setMinimumSize(0, 0);

    studentwidget    *sWidget = new studentwidget(&university, this);
    dormitorywidget  *dWidget = new dormitorywidget(&university, this);
    restaurantwidget *rWidget = new restaurantwidget(&university, this);

    tabs->addTab(sWidget, "Students");
    tabs->addTab(dWidget, "Dormitories");
    tabs->addTab(rWidget, "Restaurant");

    // refresh selectors when dormitories change
    connect(dWidget, &dormitorywidget::dormitoriesChanged,
            sWidget, &studentwidget::refreshDormitories);
    connect(dWidget, &dormitorywidget::dormitoriesChanged,
            rWidget, &restaurantwidget::refreshDormitories);

    tabs->setStyleSheet(
        "QTabBar::tab { padding: 10px 20px; background: white;"
        "border-top-left-radius: 12px; border-top-right-radius: 12px; margin-right: 2px; }"
        "QTabBar::tab:selected { background: #E74C54; color: white; }"
        );

    mainLayout->addWidget(header);
    mainLayout->addWidget(tabs);

    resize(1000, 700);
}

udrms::~udrms() {}