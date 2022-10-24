#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Test3OOp.h"

class Test3OOp : public QMainWindow
{
    Q_OBJECT

public:
    Test3OOp(QWidget *parent = Q_NULLPTR);

private:
    Ui::Test3OOpClass ui;
};
