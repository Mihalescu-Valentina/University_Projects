#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_StarGUI.h"
#include "Service.h"
#include "AstronomersTableModel.h"
#include <windows.h>

class Models
{
private:
    std::vector<AstronomersTableModel*> models;

public:
    Models() = default;
    void addModel(AstronomersTableModel* model) { this->models.push_back(model); }
    std::vector<AstronomersTableModel*> getModels() { return this->models; }
};

class StarGUI : public QMainWindow
{
    Q_OBJECT

public:
    StarGUI(Service& service,Astronomer& a,AstronomersTableModel& model,Models& models,QWidget *parent = nullptr);
    ~StarGUI();

private:
    Ui::StarGUIClass ui;
    Models& models;
    Service& service;
    AstronomersTableModel* model;
    Astronomer& a;
    void populateList();
    void connectSignalsSlots();
    void addStar();
    void updateStar();
    void showStarsConstellation(std::string name);
    //void changeSelected();
    //void populateUpdatedList();
   //void changeClosed();
};
