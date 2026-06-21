#ifndef DORMITORYWIDGET_H
#define DORMITORYWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "university.h"
#include "dormitory.h"
#include "filemanager.h"

class dormitorywidget : public QWidget {
    Q_OBJECT

public:
    explicit dormitorywidget(University *university, QWidget *parent = nullptr);

signals:
    void dormitoriesChanged();
private slots:
    void onAddClicked();
    void onCancelClicked();
    void onRemoveClicked();
    void onFindClicked();

private:
    University  *university;
    FileManager *fileManager;

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
    QLineEdit   *capacityEdit;
    QLineEdit   *totalRoomsEdit;
    QPushButton *addBtn;
    QPushButton *cancelBtn;

    // ── Remove panel widgets ─────────────────────────
    QLineEdit   *removeNameEdit;
    QListWidget *removeList;
    QPushButton *removeBtn;

    // ── Find panel widgets ───────────────────────────
    QLineEdit   *findEdit;
    QListWidget *findResultList;
    QPushButton *findBtn;
};

#endif