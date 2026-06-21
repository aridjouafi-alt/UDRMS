#include "welcome.h"
#include "ui_welcome.h"
#include "udrms.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

welcome::welcome(QWidget *parent) : QWidget(parent), ui(new Ui::welcome)
{
    ui->setupUi(this);

    // background
    setStyleSheet("background-color: #E74C54;");

    // title
    QLabel *title = new QLabel("University Dormitory & Restaurant System", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 36px; font-weight: bold; color: white; background: transparent;");

    // subtitle
    QLabel *subtitle = new QLabel("Manage students, rooms, and restaurant menus all in one place.", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setWordWrap(false);
    subtitle->setMaximumWidth(700);
    subtitle->setStyleSheet("font-size: 20px; color: #F9B4B7; background: transparent;");

    // enter button
    ui->enterButton->setFixedSize(200, 60);
    ui->enterButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   background-color: #E74C54;"
        "   color: #F5F5F0;"
        "   border-radius: 10px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: #D9434B;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #B9373F;"
        "   padding-top: 4px;"
        "   padding-left: 4px;"
        "}"
        );
    // shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(20);
    shadow->setOffset(3, 3);
    shadow->setColor(QColor(0, 0, 0, 120));
    ui->enterButton->setGraphicsEffect(shadow);

    // layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(title,    0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(subtitle, 0, Qt::AlignCenter);
    layout->addSpacing(80);
    layout->addWidget(ui->enterButton, 0, Qt::AlignCenter);
    layout->addStretch();
    setLayout(layout);
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_enterButton_clicked()
{
    try {
        udrms *w = new udrms(nullptr);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->showMaximized();
        this->close();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    } catch (...) {
        QMessageBox::critical(this, "Error", "Failed to open the main window.");
    }
}