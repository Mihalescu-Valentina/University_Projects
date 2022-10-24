#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include<qdialog.h>
class AdministratorGUI :
    public QDialog
{
    Q_OBJECT
private:
    Service& service;
    QListWidget* eventsListWidget,*typeFileListWidget;
    QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * timeLineEdit, * nrPeopleLineEdit, * linkLineEdit;
    QPushButton *addButton,*deleteButton,*updateButton;
    


public:
    explicit AdministratorGUI(Service& s, QWidget* parent = 0);

private:
    void initGUI();
    void populateRepoList();
    void connectSignalandSlots();
    int getSelectedIndex() const;
    void addEvent();
    void deleteEvent();
    void updateEvent();
};

