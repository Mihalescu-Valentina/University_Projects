#pragma once
#include <qdialog.h>
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
class UserGUI :
    public QDialog
{
    Q_OBJECT
private:
    Service& service;
    QListWidget* eventsListWidget, * typeFileListWidget,*eventsListsWidget;
    QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * timeLineEdit, * nrPeopleLineEdit, * linkLineEdit;
    QPushButton* addButton, * deleteButton, * openButton, * filterByMonthButton;

public:
    explicit UserGUI(Service& s, QWidget* parent = 0);

private:
    void initGUI();
    void populateRepoList();
    void connectSignalandSlots();
    int getSelectedIndex() const;
    void addEventList();
    void populateList();
    void openFile();
    void deleteEventList();
    int getSelectedIndexList();
    void filterMonth();
    

};

