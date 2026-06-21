#include "studentwidget.h"
#include "room.h"
#include <QMessageBox>
#include <vector>

using namespace std;

studentwidget::studentwidget(University *university, QWidget *parent)
    : QWidget(parent), university(university)
{
    fileManager = new FileManager("C:/Users/Rawnak/Documents/udrms/src/data/university.txt");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    // ── Dormitory selector row ───────────────────────
    QHBoxLayout *selectorRow = new QHBoxLayout;
    QLabel *selectorLbl = new QLabel("Dormitory");
    selectorLbl->setFixedWidth(90);
    selectorLbl->setStyleSheet(
        "QLabel { background: #E74C54; color: white; padding: 4px 8px;"
        "border-radius: 4px; font-weight: bold; border: none; }"
        );
    dormSelector = new QComboBox;
    dormSelector->setStyleSheet(
        "QComboBox { background: #F9B4B7; color: #333;"
        "border: none; border-radius: 4px; padding: 4px 8px; }"
        );
    dormSelector->setFixedHeight(32);

    // populate with all dormitories
    for (const Dormitory &d : university->getDormitories())
        dormSelector->addItem(QString::fromStdString(d.getName()));

    selectorRow->addWidget(selectorLbl);
    selectorRow->addWidget(dormSelector);
    selectorRow->addStretch();
    mainLayout->addLayout(selectorRow);

    // ── 3 panels ─────────────────────────────────────
    QHBoxLayout *panelsLayout = new QHBoxLayout;
    panelsLayout->setSpacing(12);
    panelsLayout->addWidget(buildAddPanel(),    1);
    panelsLayout->addWidget(buildRemovePanel(), 1);
    panelsLayout->addWidget(buildFindPanel(),   1);
    mainLayout->addLayout(panelsLayout, 1);

    connect(addBtn,    &QPushButton::clicked, this, &studentwidget::onAddClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &studentwidget::onCancelClicked);
    connect(removeBtn, &QPushButton::clicked, this, &studentwidget::onRemoveClicked);
    connect(findBtn,   &QPushButton::clicked, this, &studentwidget::onFindClicked);
    connect(dormSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &studentwidget::onDormitoryChanged);
}

// ── Helper ───────────────────────────────────────────────────────────────────

Dormitory *studentwidget::getSelectedDormitory() {
    if (university == nullptr) return nullptr;
    if (university->getDormitories().empty()) return nullptr;

    int index = dormSelector->currentIndex();
    if (index < 0 || index >= (int)university->getDormitories().size())
        return nullptr;

    return const_cast<Dormitory*>(&university->getDormitories()[index]);
}

void studentwidget::refreshDormitories() {
    dormSelector->clear();
    for (const Dormitory &d : university->getDormitories())
        dormSelector->addItem(QString::fromStdString(d.getName()));
}

void studentwidget::onDormitoryChanged(int index) {
    Q_UNUSED(index);
    // clear panels when dormitory changes
    removeList->clear();
    findResultList->clear();
}

// ── Style helpers ────────────────────────────────────────────────────────────

QString studentwidget::panelStyle() const {
    return "QFrame { border: 3px solid #E74C54; border-radius: 10px; background: white; }";
}

QString studentwidget::labelStyle() const {
    return "QLabel { background: #E74C54; color: white; padding: 4px 8px;"
           "border-radius: 4px; font-weight: bold; border: none; }";
}

QString studentwidget::inputStyle() const {
    return "QLineEdit, QComboBox { background: #F9B4B7; color: #333;"
           "border: none; border-radius: 4px; padding: 4px 8px; }";
}

QString studentwidget::buttonStyle() const {
    return "QPushButton { background: #E74C54; color: white; border-radius: 4px;"
           "padding: 6px 24px; font-weight: bold; border: none; }"
           "QPushButton:hover { background: #C0393F; }"
           "QPushButton:pressed { background: #7A1F23; "
           "padding-top: 4px; padding-left: 4px; }";
}

// ── Panel builders ───────────────────────────────────────────────────────────

QFrame *studentwidget::buildAddPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Add a student");
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

    nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("ex: Ouafi Aridj");

    idEdit   = new QLineEdit;
    idEdit->setPlaceholderText("ex: 202533376515");

    yearEdit = new QLineEdit;
    yearEdit->setPlaceholderText("1 to 5");

    roomEdit = new QLineEdit;
    roomEdit->setPlaceholderText("1 to 1000");

    makeRow("Full Name",     nameEdit);
    makeRow("ID",            idEdit);
    makeRow("Academic Year", yearEdit);
    makeRow("Room",          roomEdit);

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

QFrame *studentwidget::buildRemovePanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Remove a student");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    QHBoxLayout *row = new QHBoxLayout;
    QLabel *lbl = new QLabel("ID");
    lbl->setFixedWidth(110);
    lbl->setStyleSheet(labelStyle());
    removeIdEdit = new QLineEdit;
    removeIdEdit->setPlaceholderText("Enter student ID…");
    removeIdEdit->setStyleSheet(inputStyle());
    row->addWidget(lbl);
    row->addWidget(removeIdEdit);
    vl->addLayout(row);

    removeList = new QListWidget;
    removeList->setStyleSheet("border: 1px solid #F9B4B7; border-radius: 4px;");
    vl->addWidget(removeList, 1);

    removeBtn = new QPushButton("Remove");
    removeBtn->setStyleSheet(buttonStyle());
    vl->addWidget(removeBtn);

    return panel;
}

QFrame *studentwidget::buildFindPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Find a student");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    QHBoxLayout *row = new QHBoxLayout;
    QLabel *lbl = new QLabel("Name / ID");
    lbl->setFixedWidth(110);
    lbl->setStyleSheet(labelStyle());
    findEdit = new QLineEdit;
    findEdit->setPlaceholderText("Search…");
    findEdit->setStyleSheet(inputStyle());
    row->addWidget(lbl);
    row->addWidget(findEdit);
    vl->addLayout(row);

    findResultList = new QListWidget;
    findResultList->setStyleSheet("border: 1px solid #F9B4B7; border-radius: 4px;");
    vl->addWidget(findResultList, 1);

    findBtn = new QPushButton("Find");
    findBtn->setStyleSheet(buttonStyle());
    vl->addWidget(findBtn);

    return panel;
}

// ── Slots ────────────────────────────────────────────────────────────────────

void studentwidget::onAddClicked() {
    Dormitory *dormitory = getSelectedDormitory();
    if (dormitory == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    QString name = nameEdit->text().trimmed();
    QString id   = idEdit->text().trimmed();
    QString year = yearEdit->text().trimmed();
    QString room = roomEdit->text().trimmed();

    if (name.isEmpty() || id.isEmpty() || year.isEmpty() || room.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    // validate room number
    bool roomOk;
    int roomNumber = room.toInt(&roomOk);
    if (!roomOk || roomNumber < 1 || roomNumber > 1000) {
        QMessageBox::warning(this, "Error", "Room number must be between 1 and 1000.");
        return;
    }

    // check duplicate ID
    for (const Room &r : dormitory->getRooms())
        for (const Student &s : r.getOccupants())
            if (s.getId() == id.toLongLong()) {
                QMessageBox::warning(this, "Duplicate ID",
                                     "A student with ID " + id + " already exists.");
                return;
            }

    // check room exists and is available
    bool roomFound = false;
    for (const Room &r : dormitory->getRooms()) {
        if (r.getRoomNumber() == roomNumber) {
            roomFound = true;
            if (!r.isAvailable()) {
                QMessageBox::warning(this, "Error",
                                     "Room " + room + " is already occupied.");
                return;
            }
            break;
        }
    }

    if (!roomFound) {
        QMessageBox::warning(this, "Error", "Room " + room + " does not exist.");
        return;
    }

    try {
        Student student(id.toLongLong(), name.toStdString(), year.toInt());
        dormitory->assignStudentToRoom(student, roomNumber);

        fileManager->saveUniversity(*university);

        QMessageBox::information(this, "Success",
                                 "Student " + name + " added to room " + room + " successfully.");

        nameEdit->clear();
        idEdit->clear();
        yearEdit->clear();
        roomEdit->clear();

    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid Input", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void studentwidget::onCancelClicked() {
    nameEdit->clear();
    idEdit->clear();
    yearEdit->clear();
    roomEdit->clear();
}

void studentwidget::onRemoveClicked() {
    Dormitory *dormitory = getSelectedDormitory();
    if (dormitory == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    QString id = removeIdEdit->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a student ID.");
        return;
    }

    try {
        for (const Room &room : dormitory->getRooms()) {
            for (const Student &s : room.getOccupants()) {
                if (s.getId() == id.toLongLong()) {
                    dormitory->removeStudent(s);
                    fileManager->saveUniversity(*university);
                    removeList->clear();
                    removeIdEdit->clear();
                    QMessageBox::information(this, "Success",
                                             "Student removed successfully.");
                    return;
                }
            }
        }
        QMessageBox::warning(this, "Not found",
                             "No student found with ID: " + id);

    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid Input", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void studentwidget::onFindClicked() {
    Dormitory *dormitory = getSelectedDormitory();
    if (dormitory == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    QString query = findEdit->text().trimmed();
    if (query.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a name or ID.");
        return;
    }

    try {
        findResultList->clear();
        bool found = false;

        for (const Room &room : dormitory->getRooms()) {
            for (const Student &s : room.getOccupants()) {
                QString sName = QString::fromStdString(s.getFullName());
                QString sId   = QString::number(s.getId());
                QString sYear = QString::number(s.getAcademicYear());

                if (sName.contains(query, Qt::CaseInsensitive) || sId == query) {
                    findResultList->addItem(
                        "ID: "   + sId   + "  |  " +
                        "Name: " + sName + "  |  " +
                        "Year: " + sYear + "  |  " +
                        "Room: " + QString::number(room.getRoomNumber())
                        );
                    found = true;
                }
            }
        }

        if (!found)
            findResultList->addItem("No student found for: " + query);

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}