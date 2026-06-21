#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include "ui_welcome.h"

QT_BEGIN_NAMESPACE
namespace Ui { class welcome; }
QT_END_NAMESPACE

class welcome : public QWidget
{
    Q_OBJECT
public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();
private slots:
    void on_enterButton_clicked();
private:
    Ui::welcome *ui;
};

#endif