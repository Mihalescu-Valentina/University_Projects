#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PracticeTest3OOP.h"

class PracticeTest3OOP : public QMainWindow
{
    Q_OBJECT

public:
    PracticeTest3OOP(QWidget *parent = Q_NULLPTR);

private:
    Ui::PracticeTest3OOPClass ui;
};
