/********************************************************************************
** Form generated from reading UI file 'studentwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTWIDGET_H
#define UI_STUDENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_studentwidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QFrame *frame_3;
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QFrame *frame_2;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QFrame *frame;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *studentwidget)
    {
        if (studentwidget->objectName().isEmpty())
            studentwidget->setObjectName("studentwidget");
        studentwidget->resize(1101, 582);
        studentwidget->setMaximumSize(QSize(1388, 16777215));
        studentwidget->setStyleSheet(QString::fromUtf8("b"));
        layoutWidget = new QWidget(studentwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 1101, 581));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(15);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(10, 10, 10, 10);
        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #FC477A;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        groupBox_3 = new QGroupBox(frame_3);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 10, 311, 521));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    background-color: white;\n"
"}"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 0, 151, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));

        gridLayout->addWidget(frame_3, 0, 2, 1, 1);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FC477A;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 10, 311, 521));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    background-color: white;\n"
"}"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 0, 201, 31));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;"));

        gridLayout->addWidget(frame_2, 0, 1, 1, 1);

        frame = new QFrame(layoutWidget);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color: #FC477A"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 10, 311, 521));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    background-color: white;\n"
"}"));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 151, 31));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(112, 80, 181, 21));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(140, 130, 151, 21));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(140, 180, 151, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(140, 240, 151, 21));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: #FC477A;"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(180, 470, 93, 29));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 470, 93, 29));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 80, 71, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 101, 21));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 180, 101, 21));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 240, 101, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 290, 101, 21));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(140, 290, 151, 21));

        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(studentwidget);

        QMetaObject::connectSlotsByName(studentwidget);
    } // setupUi

    void retranslateUi(QWidget *studentwidget)
    {
        studentwidget->setWindowTitle(QCoreApplication::translate("studentwidget", "Form", nullptr));
        groupBox_3->setTitle(QString());
        label_3->setText(QCoreApplication::translate("studentwidget", "Find a student", nullptr));
        groupBox_2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("studentwidget", "Remove a student", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("studentwidget", "Add a student", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("studentwidget", "Ouafu Aridj", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("studentwidget", "202533376515", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("studentwidget", "1", nullptr));
        pushButton->setText(QCoreApplication::translate("studentwidget", "Add", nullptr));
        pushButton_2->setText(QCoreApplication::translate("studentwidget", "cancel", nullptr));
        label_4->setText(QCoreApplication::translate("studentwidget", "Full Name", nullptr));
        label_5->setText(QCoreApplication::translate("studentwidget", " ID", nullptr));
        label_6->setText(QCoreApplication::translate("studentwidget", "Academic Year", nullptr));
        label_7->setText(QCoreApplication::translate("studentwidget", "Dormitory", nullptr));
        label_8->setText(QCoreApplication::translate("studentwidget", "room", nullptr));
        lineEdit_4->setPlaceholderText(QCoreApplication::translate("studentwidget", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class studentwidget: public Ui_studentwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTWIDGET_H
