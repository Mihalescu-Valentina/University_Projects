#include "AdministratorUser.h"
#include "Service.h"
#include "AdministratorGUI.h"
#include "UserGUI.h"

AdministratorUser::AdministratorUser(Service& _s, QWidget* parent) :s{_s},QDialog(parent)
{
	this->initAdministratorUser();
	this->connectSignalSlots();
}

//function used to initialise the gui for choosing between user mode and administrator mode
void AdministratorUser::initAdministratorUser()
{
	this->administratorUserLayout = new QVBoxLayout(this);
	this->administratorUserButtonsLayout = new QGridLayout();
	this->userButton = new QPushButton("User");
	this->administratorButton = new QPushButton("Administrator");
	this->administratorUserButtonsLayout->addWidget(this->administratorButton, 0, 0);
	this->administratorUserButtonsLayout->addWidget(this->userButton, 0, 1);
	this->administratorUserLayout->addLayout(administratorUserButtonsLayout);
}

//function used for making connections
void AdministratorUser::connectSignalSlots()
{
	QObject::connect(this->administratorButton, &QPushButton::clicked, this, &AdministratorUser::runAdministrator);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &AdministratorUser::runUser);
}

//function used when choosing to enter the administrator mode
void AdministratorUser::runAdministrator()
{
	AdministratorGUI gui{ this->s };
	gui.exec();

}

//function used when choosing to enter the user mode
void AdministratorUser::runUser()
{
	UserGUI gui{ this->s };
	gui.exec();
}
