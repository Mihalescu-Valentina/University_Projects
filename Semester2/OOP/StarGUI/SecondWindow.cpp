#pragma once
#include <QtWidgets/QMainWindow>
#include "SecondWindow.h"
#include<qmessagebox.h>

SecondWindow::SecondWindow(const char* name, Service& s, QWidget* parent)
    :s{ s }, QDialog(parent) {
    this->setWindowTitle(name);
    this->init();
    this->populateList();
    this->connectSignalsAndSlots();

}

SecondWindow::~SecondWindow() {

}

void SecondWindow::init() {

    this->mainLayout = new QVBoxLayout(this);
    this->viewButton = new QPushButton("View");
    this->viewLineEdit = new QLineEdit();
    this->listWidget = new QListWidget();
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(this->viewButton, 0, 0);
    grid->addWidget(this->viewLineEdit, 0, 1);
    this->mainLayout->addWidget(this->listWidget);
    this->mainLayout->addLayout(grid);
}


void SecondWindow::connectSignalsAndSlots() {
   QObject::connect(this->viewButton, &QPushButton::clicked, this, &SecondWindow::showSearch);
}

void SecondWindow::showSearch() {
    std::string name = this->viewLineEdit->text().toStdString();
    if (name != " ") {
        this->listWidget->clear();
        Star s = this->s.searchStar(name);
        std::vector<Star> elems = this->s.starsConstellation(s.getConstellation());
        for (int i = 0; i < elems.size(); i++) {
            std::string str = elems[i].getName() + "," + elems[i].getConstellation() + "," + std::to_string(elems[i].getRa()) + "," + std::to_string(elems[i].getDec()) + "," + std::to_string(elems[i].getDiameter());
            this->listWidget->addItem(QString::fromStdString(str));
        }
    }

    else
    {
        QMessageBox::critical(this, "Error", "The entity was already added to your list!");
        return;
    }
}

void SecondWindow::populateList() {
    std::vector<Star> elems = this->s.getStars();
    for (int i = 0; i < elems.size(); i++) {
        std::string str = elems[i].getName() + ","+elems[i].getConstellation()+","+std::to_string(elems[i].getRa()) + "," + std::to_string(elems[i].getDec()) + "," + std::to_string(elems[i].getDiameter());
        this->listWidget->addItem(QString::fromStdString(str));
    }

}



