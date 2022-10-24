#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HomeWork1112QtGUI.h"

class HomeWork1112QtGUI : public QMainWindow
{
    Q_OBJECT

public:
    HomeWork1112QtGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::HomeWork1112QtGUIClass ui;
};
