#include "dormitorywidget.h"
#include "menu.h"
#include "restaurant.h"
#include <QMessageBox>
#include <vector>

using namespace std;

dormitorywidget::dormitorywidget(University *university, QWidget *parent)
    : QWidget(parent), university(university)
{
    fileManager = new FileManager("C:/Users/Rawnak/Documents/udrms/src/data/university.txt");

    QHBoxLayout *root = new QHBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(12);

    root->addWidget(buildAddPanel(),    1);
    root->addWidget(buildRemovePanel(), 1);
    root->addWidget(buildFindPanel(),   1);

    connect(addBtn,    &QPushButton::clicked, this, &dormitorywidget::onAddClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &dormitorywidget::onCancelClicked);
    connect(removeBtn, &QPushButton::clicked, this, &dormitorywidget::onRemoveClicked);
    connect(findBtn,   &QPushButton::clicked, this, &dormitorywidget::onFindClicked);
}

// ── Style helpers ────────────────────────────────────────────────────────────

QString dormitorywidget::panelStyle() const {
    return "QFrame { border: 3px solid #E74C54; border-radius: 10px; background: white; }";
}

QString dormitorywidget::labelStyle() const {
    return "QLabel { background: #E74C54; color: white; padding: 4px 8px;"
           "border-radius: 4px; font-weight: bold; border: none; }";
}

QString dormitorywidget::inputStyle() const {
    return "QLineEdit, QComboBox { background: #F9B4B7; color: #333;"
           "border: none; border-radius: 4px; padding: 4px 8px; }";
}

QString dormitorywidget::buttonStyle() const {
    return "QPushButton { background: #E74C54; color: white; border-radius: 4px;"
           "padding: 6px 24px; font-weight: bold; border: none; }"
           "QPushButton:hover { background: #C0393F; }";
}

// ── Panel builders ───────────────────────────────────────────────────────────

QFrame *dormitorywidget::buildAddPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Add a dormitory");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    auto makeRow = [&](const QString &lbl, QWidget *input) {
        QHBoxLayout *row = new QHBoxLayout;
        QLabel *l = new QLabel(lbl);
        l->setFixedWidth(110);
        l->setStyleSheet(labelStyle());
        input->setStyleSheet(inputStyle());
        row->addWidget(l);
        row->addWidget(input);
        vl->addLayout(row);
    };

    nameEdit       = new QLineEdit;
    capacityEdit   = new QLineEdit;
    totalRoomsEdit = new QLineEdit;

    makeRow("Name",        nameEdit);
    makeRow("Capacity",    capacityEdit);
    makeRow("Total Rooms", totalRoomsEdit);

    vl->addStretch();

    QHBoxLayout *btnRow = new QHBoxLayout;
    cancelBtn = new QPushButton("cancel");
    addBtn    = new QPushButton("Add");
    cancelBtn->setStyleSheet(buttonStyle());
    addBtn->setStyleSheet(buttonStyle());
    btnRow->addWidget(cancelBtn);
    btnRow->addWidget(addBtn);
    vl->addLayout(btnRow);

    return panel;
}

QFrame *dormitorywidget::buildRemovePanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Remove a dormitory");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    QHBoxLayout *row = new QHBoxLayout;
    QLabel *lbl = new QLabel("Name");
    lbl->setFixedWidth(110);
    lbl->setStyleSheet(labelStyle());
    removeNameEdit = new QLineEdit;
    removeNameEdit->setPlaceholderText("Enter dormitory name…");
    removeNameEdit->setStyleSheet(inputStyle());
    row->addWidget(lbl);
    row->addWidget(removeNameEdit);
    vl->addLayout(row);

    removeList = new QListWidget;
    removeList->setStyleSheet("border: 1px solid #F7A8BC; border-radius: 4px;");
    vl->addWidget(removeList, 1);

    removeBtn = new QPushButton("Remove");
    removeBtn->setStyleSheet(buttonStyle());
    vl->addWidget(removeBtn);

    return panel;
}

QFrame *dormitorywidget::buildFindPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Find a dormitory");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    QHBoxLayout *row = new QHBoxLayout;
    QLabel *lbl = new QLabel("Name");
    lbl->setFixedWidth(110);
    lbl->setStyleSheet(labelStyle());
    findEdit = new QLineEdit;
    findEdit->setPlaceholderText("Search by name…");
    findEdit->setStyleSheet(inputStyle());
    row->addWidget(lbl);
    row->addWidget(findEdit);
    vl->addLayout(row);

    findResultList = new QListWidget;
    findResultList->setStyleSheet("border: 1px solid #F7A8BC; border-radius: 4px;");
    vl->addWidget(findResultList, 1);

    findBtn = new QPushButton("Find");
    findBtn->setStyleSheet(buttonStyle());
    vl->addWidget(findBtn);

    return panel;
}

// ── Slots ────────────────────────────────────────────────────────────────────

void dormitorywidget::onAddClicked() {
    if (university == nullptr) return;

    QString name       = nameEdit->text().trimmed();
    QString capacity   = capacityEdit->text().trimmed();
    QString totalRooms = totalRoomsEdit->text().trimmed();

    if (name.isEmpty() || capacity.isEmpty() || totalRooms.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    bool capOk, roomsOk;
    int cap   = capacity.toInt(&capOk);
    int rooms = totalRooms.toInt(&roomsOk);

    if (!capOk || cap <= 0) {
        QMessageBox::warning(this, "Error", "Capacity must be a positive number.");
        return;
    }

    if (!roomsOk || rooms <= 0) {
        QMessageBox::warning(this, "Error", "Total rooms must be a positive number.");
        return;
    }

    try {
        Menu menu({"Coffee", "Bread", "Eggs"},
                  {"Soup", "Couscous", "Salad"},
                  {"Chicken", "Rice", "Fruit"});
        Restaurant restaurant(1, "Main Restaurant", menu);
        Dormitory newDorm(name.toStdString(), cap, rooms, restaurant);

        // add rooms to dormitory
        vector<Room> roomList;
        for (int i = 1; i <= rooms; i++)
            roomList.push_back(Room(i, 1));
        newDorm.setRooms(roomList);

        university->addDormitory(newDorm);
        fileManager->saveUniversity(*university);
        emit dormitoriesChanged();

        QMessageBox::information(this, "Success",
                                 "Dormitory " + name + " added successfully.");

        nameEdit->clear();
        capacityEdit->clear();
        totalRoomsEdit->clear();

    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid Input", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void dormitorywidget::onCancelClicked() {
    nameEdit->clear();
    capacityEdit->clear();
    totalRoomsEdit->clear();
}

void dormitorywidget::onRemoveClicked() {
    if (university == nullptr) return;

    QString name = removeNameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a dormitory name.");
        return;
    }

    try {
        university->removeDormitory(name.toStdString());
        fileManager->saveUniversity(*university);
        emit dormitoriesChanged();

        removeList->clear();
        removeNameEdit->clear();
        QMessageBox::information(this, "Success",
                                 "Dormitory " + name + " removed successfully.");

    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid Input", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void dormitorywidget::onFindClicked() {
    if (university == nullptr) return;

    QString query = findEdit->text().trimmed();
    if (query.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a dormitory name.");
        return;
    }

    try {
        findResultList->clear();
        bool found = false;

        for (const Dormitory &d : university->getDormitories()) {
            QString dName = QString::fromStdString(d.getName());

            if (dName.contains(query, Qt::CaseInsensitive)) {
                // count occupied rooms
                int occupied = 0;
                for (const Room &r : d.getRooms())
                    if (!r.getOccupants().empty())
                        occupied++;

                findResultList->addItem(
                    "Name: "        + dName +
                    "  |  Capacity: "    + QString::number(d.getCapacity()) +
                    "  |  Total Rooms: " + QString::number(d.getTotalRooms()) +
                    "  |  Occupied: "    + QString::number(occupied)
                    );
                found = true;
            }
        }

        if (!found)
            findResultList->addItem("No dormitory found for: " + query);

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}