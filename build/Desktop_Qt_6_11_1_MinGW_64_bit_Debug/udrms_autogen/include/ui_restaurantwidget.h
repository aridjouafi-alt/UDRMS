/********************************************************************************
** Form generated from reading UI file 'restaurantwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTWIDGET_H
#define UI_RESTAURANTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_restaurantwidget
{
public:

    void setupUi(QWidget *restaurantwidget)
    {
        if (restaurantwidget->objectName().isEmpty())
            restaurantwidget->setObjectName("restaurantwidget");
        restaurantwidget->resize(400, 300);

        retranslateUi(restaurantwidget);

        QMetaObject::connectSlotsByName(restaurantwidget);
    } // setupUi

    void retranslateUi(QWidget *restaurantwidget)
    {
        restaurantwidget->setWindowTitle(QCoreApplication::translate("restaurantwidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class restaurantwidget: public Ui_restaurantwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTWIDGET_H
