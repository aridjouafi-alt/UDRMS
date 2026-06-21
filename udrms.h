#ifndef UDRMS_H
#define UDRMS_H

#include <QMainWindow>
#include "dormitory.h"
#include "university.h"
#include "restaurant.h"

QT_BEGIN_NAMESPACE
class QTabWidget;
QT_END_NAMESPACE

class udrms : public QMainWindow
{
    Q_OBJECT

public:
    explicit udrms(QWidget *parent = nullptr);
    ~udrms() override;

private:
    QTabWidget *tabs;
    Dormitory *dormitory = nullptr;
    University university;

};

#endif