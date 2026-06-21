#ifndef RESTAURANTWIDGET_H
#define RESTAURANTWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "university.h"
#include "filemanager.h"

class restaurantwidget : public QWidget {
    Q_OBJECT

public:
    explicit restaurantwidget(University *university, QWidget *parent = nullptr);
    void refreshDormitories();  // called from outside when new dorm is added

private slots:
    void onAddClicked();
    void onCancelClicked();
    void onRemoveClicked();
    void onServeMealClicked();
    void onDormitoryChanged(int index);
    void refreshMenu();

private:
    University  *university;
    FileManager *fileManager;

    // ── Dormitory selector ───────────────────────────
    QComboBox   *dormSelector;

    // ── Panel builders ───────────────────────────────
    QFrame *buildAddPanel();
    QFrame *buildRemovePanel();
    QFrame *buildDisplayPanel();

    // ── Style helpers ────────────────────────────────
    QString panelStyle()  const;
    QString labelStyle()  const;
    QString inputStyle()  const;
    QString buttonStyle() const;

    // ── Add panel widgets ────────────────────────────
    QLineEdit   *itemNameEdit;
    QComboBox   *categoryCombo;
    QPushButton *addBtn;
    QPushButton *cancelBtn;

    // ── Remove panel widgets ─────────────────────────
    QLineEdit   *removeItemEdit;
    QComboBox   *removeCategoryCombo;
    QListWidget *removeList;
    QPushButton *removeBtn;

    // ── Display panel widgets ────────────────────────
    QListWidget *menuList;
    QLabel      *mealsServedLabel;
    QPushButton *serveMealBtn;

    // ── Helper ───────────────────────────────────────
    Dormitory *getSelectedDormitory();
};

#endif