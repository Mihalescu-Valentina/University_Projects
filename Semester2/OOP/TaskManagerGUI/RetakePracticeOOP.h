#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_RetakePracticeOOP.h"
#include "Service.h"
#include "Programmer.h"
#include "Observer.h"

class MyException : public std::exception
{
private:
    std::string message;

public:
    MyException(const std::string& s) : message{ s } {}

    const char* what() const throw() override {
        return this->message.c_str();
    }
};

class TaskManager : public QMainWindow,public Observer
{

    Q_OBJECT

public:
    TaskManager(Service& s,Programmer& p,QWidget *parent = nullptr);
    ~TaskManager();

private:
    Service& service;
    Programmer& p;
    Ui::RetakePracticeOOPClass ui;
    void populateList();
    void connectSignalsSlots();
    void update() override;
    void addTask();
    void removeTask();
    void changeSelected();
    void populateUpdatedList();
    friend class MyException;
    
};
