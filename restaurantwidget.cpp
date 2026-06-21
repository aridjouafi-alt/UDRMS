#include "restaurantwidget.h"
#include "dormitory.h"
#include "menu.h"
#include "restaurant.h"
#include <QMessageBox>
#include <vector>

using namespace std;

restaurantwidget::restaurantwidget(University *university, QWidget *parent)
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
    panelsLayout->addWidget(buildAddPanel(),     1);
    panelsLayout->addWidget(buildRemovePanel(),  1);
    panelsLayout->addWidget(buildDisplayPanel(), 1);
    mainLayout->addLayout(panelsLayout, 1);

    connect(addBtn,       &QPushButton::clicked,        this, &restaurantwidget::onAddClicked);
    connect(cancelBtn,    &QPushButton::clicked,        this, &restaurantwidget::onCancelClicked);
    connect(removeBtn,    &QPushButton::clicked,        this, &restaurantwidget::onRemoveClicked);
    connect(serveMealBtn, &QPushButton::clicked,        this, &restaurantwidget::onServeMealClicked);
    connect(dormSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &restaurantwidget::onDormitoryChanged);

    refreshMenu();
}

// ── Style helpers ────────────────────────────────────────────────────────────

QString restaurantwidget::panelStyle() const {
    return "QFrame { border: 3px solid #E74C54; border-radius: 10px; background: white; }";
}

QString restaurantwidget::labelStyle() const {
    return "QLabel { background: #E74C54; color: white; padding: 4px 8px;"
           "border-radius: 4px; font-weight: bold; border: none; }";
}

QString restaurantwidget::inputStyle() const {
    return "QLineEdit, QComboBox { background: #F9B4B7; color: #333;"
           "border: none; border-radius: 4px; padding: 4px 8px; }";
}

QString restaurantwidget::buttonStyle() const {
    return "QPushButton { background: #E74C54; color: white; border-radius: 4px;"
           "padding: 6px 24px; font-weight: bold; border: none; }"
           "QPushButton:hover { background: #C0393F; }"
           "QPushButton:pressed { background: #7A1F23; }";
}

// ── Helper ───────────────────────────────────────────────────────────────────

Dormitory *restaurantwidget::getSelectedDormitory() {
    if (university == nullptr) return nullptr;
    if (university->getDormitories().empty()) return nullptr;

    int index = dormSelector->currentIndex();
    if (index < 0 || index >= (int)university->getDormitories().size())
        return nullptr;

    return const_cast<Dormitory*>(&university->getDormitories()[index]);
}

void restaurantwidget::refreshDormitories() {
    dormSelector->clear();
    for (const Dormitory &d : university->getDormitories())
        dormSelector->addItem(QString::fromStdString(d.getName()));
    refreshMenu();
}

// ── Panel builders ───────────────────────────────────────────────────────────

QFrame *restaurantwidget::buildAddPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Add a menu item");
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

    itemNameEdit  = new QLineEdit;
    categoryCombo = new QComboBox;
    categoryCombo->addItems({"Breakfast", "Lunch", "Dinner"});

    makeRow("Item Name", itemNameEdit);
    makeRow("Category",  categoryCombo);

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

QFrame *restaurantwidget::buildRemovePanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Remove a menu item");
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

    removeItemEdit      = new QLineEdit;
    removeItemEdit->setPlaceholderText("Enter item name…");
    removeCategoryCombo = new QComboBox;
    removeCategoryCombo->addItems({"Breakfast", "Lunch", "Dinner"});

    makeRow("Item Name", removeItemEdit);
    makeRow("Category",  removeCategoryCombo);

    removeList = new QListWidget;
    removeList->setStyleSheet("border: 1px solid #F9B4B7; border-radius: 4px;");
    vl->addWidget(removeList, 1);

    removeBtn = new QPushButton("Remove");
    removeBtn->setStyleSheet(buttonStyle());
    vl->addWidget(removeBtn);

    return panel;
}

QFrame *restaurantwidget::buildDisplayPanel() {
    QFrame *panel = new QFrame;
    panel->setStyleSheet(panelStyle());
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vl = new QVBoxLayout(panel);
    vl->setContentsMargins(16, 16, 16, 16);
    vl->setSpacing(12);

    QLabel *title = new QLabel("Menu");
    title->setStyleSheet("font-size: 16px; font-weight: bold; border: none;");
    vl->addWidget(title);

    menuList = new QListWidget;
    menuList->setStyleSheet("border: 1px solid #F9B4B7; border-radius: 4px;");
    vl->addWidget(menuList, 1);

    // meals served row
    QHBoxLayout *servedRow = new QHBoxLayout;
    QLabel *servedLbl = new QLabel("Meals served:");
    servedLbl->setStyleSheet("font-weight: bold; border: none;");
    mealsServedLabel = new QLabel("0");
    mealsServedLabel->setStyleSheet(
        "background: #F9B4B7; color: #7A1F23; padding: 4px 12px;"
        "border-radius: 4px; font-weight: bold; border: none;");
    servedRow->addWidget(servedLbl);
    servedRow->addWidget(mealsServedLabel);
    servedRow->addStretch();
    vl->addLayout(servedRow);

    serveMealBtn = new QPushButton("Serve a meal");
    serveMealBtn->setStyleSheet(buttonStyle());
    vl->addWidget(serveMealBtn);

    return panel;
}

// ── Slots ────────────────────────────────────────────────────────────────────

void restaurantwidget::onDormitoryChanged(int index) {
    Q_UNUSED(index);
    refreshMenu();
}

void restaurantwidget::refreshMenu() {
    Dormitory *dorm = getSelectedDormitory();
    if (dorm == nullptr) {
        menuList->clear();
        mealsServedLabel->setText("0");
        return;
    }

    const Menu &menu = dorm->getRestaurant().getMenu();
    menuList->clear();

    menuList->addItem("── Breakfast ──");
    for (const string &item : menu.getBreakfast())
        menuList->addItem("  " + QString::fromStdString(item));

    menuList->addItem("── Lunch ──");
    for (const string &item : menu.getLunch())
        menuList->addItem("  " + QString::fromStdString(item));

    menuList->addItem("── Dinner ──");
    for (const string &item : menu.getDinner())
        menuList->addItem("  " + QString::fromStdString(item));

    mealsServedLabel->setText(QString::number(menu.getMealsServed()));
}

void restaurantwidget::onAddClicked() {
    Dormitory *dorm = getSelectedDormitory();
    if (dorm == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    QString itemName = itemNameEdit->text().trimmed();
    QString category = categoryCombo->currentText();

    if (itemName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an item name.");
        return;
    }

    try {
        Restaurant &rest = const_cast<Restaurant&>(dorm->getRestaurant());
        Menu menu = rest.getMenu();

        vector<string> breakfast = menu.getBreakfast();
        vector<string> lunch     = menu.getLunch();
        vector<string> dinner    = menu.getDinner();

        if      (category == "Breakfast") breakfast.push_back(itemName.toStdString());
        else if (category == "Lunch")     lunch.push_back(itemName.toStdString());
        else                              dinner.push_back(itemName.toStdString());

        Menu newMenu(breakfast, lunch, dinner);
        rest.setMenu(newMenu);

        fileManager->saveUniversity(*university);
        refreshMenu();

        QMessageBox::information(this, "Success",
                                 itemName + " added to " + category + " successfully.");

        itemNameEdit->clear();
        categoryCombo->setCurrentIndex(0);

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void restaurantwidget::onCancelClicked() {
    itemNameEdit->clear();
    categoryCombo->setCurrentIndex(0);
}

void restaurantwidget::onRemoveClicked() {
    Dormitory *dorm = getSelectedDormitory();
    if (dorm == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    QString itemName = removeItemEdit->text().trimmed();
    QString category = removeCategoryCombo->currentText();

    if (itemName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an item name.");
        return;
    }

    try {
        Restaurant &rest = const_cast<Restaurant&>(dorm->getRestaurant());
        Menu menu = rest.getMenu();

        vector<string> breakfast = menu.getBreakfast();
        vector<string> lunch     = menu.getLunch();
        vector<string> dinner    = menu.getDinner();

        bool found = false;
        string target = itemName.toStdString();

        auto removeItem = [&](vector<string> &v) {
            for (auto it = v.begin(); it != v.end(); ++it) {
                if (*it == target) {
                    v.erase(it);
                    found = true;
                    return;
                }
            }
        };

        if      (category == "Breakfast") removeItem(breakfast);
        else if (category == "Lunch")     removeItem(lunch);
        else                              removeItem(dinner);

        if (!found) {
            QMessageBox::warning(this, "Not found",
                                 itemName + " not found in " + category + ".");
            return;
        }

        Menu newMenu(breakfast, lunch, dinner);
        rest.setMenu(newMenu);

        fileManager->saveUniversity(*university);
        refreshMenu();

        removeList->clear();
        removeItemEdit->clear();
        QMessageBox::information(this, "Success",
                                 itemName + " removed from " + category + " successfully.");

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void restaurantwidget::onServeMealClicked() {
    Dormitory *dorm = getSelectedDormitory();
    if (dorm == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a dormitory first.");
        return;
    }

    try {
        Restaurant &rest = const_cast<Restaurant&>(dorm->getRestaurant());
        rest.serveMeal();

        fileManager->saveUniversity(*university);
        refreshMenu();

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}