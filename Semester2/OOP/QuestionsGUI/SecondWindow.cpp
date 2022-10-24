#pragma once
#include <QtWidgets/QMainWindow>
#include "SecondWindow.h"
#include<qmessagebox.h>

SecondWindow::SecondWindow(const char* name,Service &s,QWidget* parent)
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
    this->searchButton = new QPushButton("Search");
    this->searchLineEdit = new QLineEdit();
    this->listWidget = new QListWidget();
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(this->searchButton, 0, 0);
    grid->addWidget(this->searchLineEdit, 0, 1);
    this->mainLayout->addWidget(this->listWidget);
    this->mainLayout->addLayout(grid);
}


void SecondWindow::connectSignalsAndSlots() {
    QObject::connect(this->searchButton, &QPushButton::clicked, this, &SecondWindow::showSearch);
}

void SecondWindow::showSearch() {
    std::string name = this->searchLineEdit->text().toStdString();
    if (name != " ") {
        this->listWidget->clear();
        Question q = this->s.Search(name);
        std::vector<Answer> questions = this->s.getMostVoted(q);
        for (int i = 0; i < questions.size(); i++) {
            std::string str = std::to_string(questions[i].getAnswerId()) + ", " + std::to_string(questions[i].getQuestionId()) + "," + questions[i].getName() + "," + questions[i].getText() + "," + std::to_string(questions[i].getNrVotes());
            this->listWidget->addItem(QString::fromStdString(str));
            
                this->listWidget->item(i)->setBackground(Qt::yellow);
                QFont font = this->listWidget->item(i)->font();
                font.setBold(true);
                //font.setItalic(true);
                //font.setUnderline(true);
                //font.setOverline(true);
                //this->listWidget->item(i)->setFont(font);

            
            
        }
    }

    else
    {
    QMessageBox::critical(this, "Error", "The entity was already added to your list!");
    return;
    }
}
            
    void SecondWindow::populateList() {
        std::vector<Answer> answers = this->s.getAnswers();
        for (int i = 0; i < answers.size(); i++) {
            std::string str = std::to_string(answers[i].getAnswerId()) + ", " + std::to_string(answers[i].getQuestionId()) + "," + answers[i].getName() + "," + answers[i].getText() + "," + std::to_string(answers[i].getNrVotes());
            this->listWidget->addItem(QString::fromStdString(str));
        }

}


