#pragma once
#include <qdialog.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include "Service.h"
class AdministratorUser :
    public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* administratorUserLayout;
    QGridLayout* administratorUserButtonsLayout;
    QPushButton* userButton, * administratorButton;
    Service& s;

public:

    explicit AdministratorUser(Service& s,QWidget* parent = 0);

private:
    void initAdministratorUser();
    void connectSignalSlots();
    void runAdministrator();
    void runUser();

};

