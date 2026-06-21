#pragma once

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <vector>
#include "university.h"
#include "dormitory.h"
#include "filemanager.h"

class studentwidget : public QWidget {
    Q_OBJECT

public:
    explicit studentwidget(University *university, QWidget *parent = nullptr);
    void refreshDormitories();

private slots:
    void onAddClicked();
    void onCancelClicked();
    void onRemoveClicked();
    void onFindClicked();
    void onDormitoryChanged(int index);

private:
    University  *university;
    FileManager *fileManager;

    // ── Dormitory selector ───────────────────────────
    QComboBox   *dormSelector;

    // ── Panel builders ───────────────────────────────
    QFrame *buildAddPanel();
    QFrame *buildRemovePanel();
    QFrame *buildFindPanel();

    // ── Style helpers ────────────────────────────────
    QString panelStyle()  const;
    QString labelStyle()  const;
    QString inputStyle()  const;
    QString buttonStyle() const;

    // ── Add panel widgets ────────────────────────────
    QLineEdit   *nameEdit;
    QLineEdit   *idEdit;
    QLineEdit   *yearEdit;
    QLineEdit   *roomEdit;
    QPushButton *addBtn;
    QPushButton *cancelBtn;

    // ── Remove panel widgets ─────────────────────────
    QLineEdit   *removeIdEdit;
    QListWidget *removeList;
    QPushButton *removeBtn;

    // ── Find panel widgets ───────────────────────────
    QLineEdit   *findEdit;
    QListWidget *findResultList;
    QPushButton *findBtn;

    // ── Helper ───────────────────────────────────────
    Dormitory *getSelectedDormitory();
};