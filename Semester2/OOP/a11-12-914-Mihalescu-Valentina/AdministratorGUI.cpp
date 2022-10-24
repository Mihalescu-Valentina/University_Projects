#include "AdministratorGUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include<sstream>
#include <qmessagebox.h>
using namespace std;
AdministratorGUI::AdministratorGUI(Service& s, QWidget* parent): service{s}, QDialog(parent)
{
	this->initGUI();
	this->populateRepoList();
	this->connectSignalandSlots();
}

//function used for initialising the GUI
void AdministratorGUI::initGUI()
{
	this->eventsListWidget = new QListWidget();
	this->typeFileListWidget = new QListWidget();
	this->titleLineEdit = new QLineEdit();
	this->descriptionLineEdit = new QLineEdit();
	this->dateLineEdit = new QLineEdit();
	this->timeLineEdit = new QLineEdit();
	this->nrPeopleLineEdit = new QLineEdit();
	
	this->linkLineEdit = new QLineEdit();
	this->addButton = new QPushButton("Add");
	this->addButton->setStyleSheet("background-color: red");
	this->deleteButton = new QPushButton("Delete");
	this->updateButton = new QPushButton("Update");
	this->updateButton->setStyleSheet("background-color: purple");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(this->eventsListWidget);

	QFormLayout* eventsDetailsLayout = new QFormLayout();
	eventsDetailsLayout->addRow("Title", this->titleLineEdit);
	eventsDetailsLayout->addRow("Description", this->descriptionLineEdit);
	eventsDetailsLayout->addRow("Date", this->dateLineEdit);
	eventsDetailsLayout->addRow("Time", this->timeLineEdit);
	eventsDetailsLayout->addRow("Nr of people", this->nrPeopleLineEdit);
	eventsDetailsLayout->addRow("Link", this->linkLineEdit);

	mainLayout->addLayout(eventsDetailsLayout);

	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);
	buttonsLayout->addWidget(this->updateButton, 1, 0);

	mainLayout->addLayout(buttonsLayout);
	

}

//function used for changing the state of the events from the repo
void AdministratorGUI::populateRepoList()
{
	this->eventsListWidget->clear();

	vector<Event>allEvents = this->service.getElemsRepo();
	
	for (Event& e : allEvents) {
		this->eventsListWidget->addItem(QString::fromStdString(e.getTitle() + " " + e.getDescription() + " " + e.getDate().getDay() + "-" + e.getDate().getMonth() + "-" + e.getDate().getYear() + " " + e.getTime() + " " + to_string(e.getNrPeople()) + " " + e.getLink()));
		
	}
}

//function used for making connections
void AdministratorGUI::connectSignalandSlots()
{
	QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Event e = this->service.getElemsRepo()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(e.getTitle()));
		this->descriptionLineEdit->setText(QString::fromStdString(e.getDescription()));
		this->dateLineEdit->setText(QString::fromStdString(e.getDate().getDay())+"-"+QString::fromStdString(e.getDate().getMonth()) +"-"+ QString::fromStdString(e.getDate().getYear()));
		this->timeLineEdit->setText(QString::fromStdString(e.getTime()));
		this->nrPeopleLineEdit->setText(QString::fromStdString(to_string(e.getNrPeople())));
		this->linkLineEdit->setText(QString::fromStdString(e.getLink()));
		
		
		});
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdministratorGUI::addEvent);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdministratorGUI::deleteEvent);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdministratorGUI::updateEvent);
}

//function that returns the selected index from the events list
int AdministratorGUI::getSelectedIndex() const
{   
	QModelIndexList selectedIndexes = this->eventsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
	
}

//function used for adding an event to the events list-administrator mode
void AdministratorGUI::addEvent()
{
	string title = this->titleLineEdit->text().toStdString();
	string description = this->descriptionLineEdit->text().toStdString();
	string date = this->dateLineEdit->text().toStdString();
	string time = this->timeLineEdit->text().toStdString();
	string nrPeople = this->nrPeopleLineEdit->text().toStdString();
	string eventLink = this->linkLineEdit->text().toStdString();
	
	char del = '-';
	vector<string> words{};
	stringstream sstream(date);
	string word;
	while (std::getline(sstream, word, del))
		words.push_back(word);
	string day = words[0];
	string month  = words[1];
	string year = words[2];
	Date data = Date(day, month, year);
	Event e = Event(title, description, data, time, stoi(nrPeople), eventLink);
	if(this->service.findEventRepo(e.getTitle(),e.getDescription()) == 1)
	    this->service.addEvent(e);
	else
	{
		QMessageBox::critical(this, "Error", "The event was already added!");
		return;
	}
	this->populateRepoList();
	int lastElement = this->service.getElemsRepo().size() - 1;
	this->eventsListWidget->setCurrentRow(lastElement);
}

//function used for deleting an event from the eventslist -administrator mode
void AdministratorGUI::deleteEvent()
{
	int index = this->getSelectedIndex();
	if (index < 0)
	{
		QMessageBox::critical(this, "Error","No event was selected");
	    return;
    }
	this->service.remove(this->service.getElemsRepo()[index].getTitle());
	this->populateRepoList();
}

//function used for updating an event from the events list repo - administrator
void AdministratorGUI::updateEvent()
{
	int index = this->getSelectedIndex();
	if (index < 0)
	{
		QMessageBox::critical(this, "Error", "No event was selected");
		return;
	}
	string title = this->titleLineEdit->text().toStdString();
	string description = this->descriptionLineEdit->text().toStdString();
	string date = this->dateLineEdit->text().toStdString();
	string time = this->timeLineEdit->text().toStdString();
	string nrPeople = this->nrPeopleLineEdit->text().toStdString();
	string eventLink = this->linkLineEdit->text().toStdString();

	char del = '-';
	vector<string> words{};
	stringstream sstream(date);
	string word;
	while (std::getline(sstream, word, del))
		words.push_back(word);
	string day = words[0];
	string month = words[1];
	string year = words[2];
	Date data = Date(day, month, year);
	Event e = Event(title, description, data, time, stoi(nrPeople), eventLink);
	this->service.update(title, description, e);
	this->populateRepoList();
	this->eventsListWidget->setCurrentRow(index);

}