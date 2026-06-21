/********************************************************************************
** Form generated from reading UI file 'dormitorywidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DORMITORYWIDGET_H
#define UI_DORMITORYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dormitorywidget
{
public:

    void setupUi(QWidget *dormitorywidget)
    {
        if (dormitorywidget->objectName().isEmpty())
            dormitorywidget->setObjectName("dormitorywidget");
        dormitorywidget->resize(400, 300);

        retranslateUi(dormitorywidget);

        QMetaObject::connectSlotsByName(dormitorywidget);
    } // setupUi

    void retranslateUi(QWidget *dormitorywidget)
    {
        dormitorywidget->setWindowTitle(QCoreApplication::translate("dormitorywidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dormitorywidget: public Ui_dormitorywidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DORMITORYWIDGET_H
