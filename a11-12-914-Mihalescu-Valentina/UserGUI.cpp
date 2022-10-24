#include "UserGui.h"
#include "AdministratorGUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include<sstream>
using namespace std;
UserGUI::UserGUI(Service& s, QWidget* parent) : service{ s }, QDialog(parent)
{
	this->initGUI();
	this->populateRepoList();
	this->populateList();
	this->connectSignalandSlots();
}

//function used for initialising the user gui
void UserGUI::initGUI()
{
	this->eventsListWidget = new QListWidget();
	this->eventsListsWidget = new QListWidget();
	this->typeFileListWidget = new QListWidget();
	this->titleLineEdit = new QLineEdit();
	this->descriptionLineEdit = new QLineEdit();
	this->dateLineEdit = new QLineEdit();
	this->timeLineEdit = new QLineEdit();
	this->nrPeopleLineEdit = new QLineEdit();

	this->linkLineEdit = new QLineEdit();
	this->addButton = new QPushButton("Add to list");
	this->deleteButton = new QPushButton("Delete from list");
	this->openButton = new QPushButton("Open file");
	this->filterByMonthButton = new QPushButton("Filter by month");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QGridLayout* EventsListsLayout = new QGridLayout();
	EventsListsLayout->addWidget(this->eventsListsWidget, 0, 1);
	EventsListsLayout->addWidget(this->eventsListWidget, 0, 0);
	mainLayout->addLayout(EventsListsLayout);

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
	buttonsLayout->addWidget(this->deleteButton, 1, 0);
	buttonsLayout->addWidget(this->openButton, 1, 1);
	buttonsLayout->addWidget(this->filterByMonthButton, 0, 1);

	mainLayout->addLayout(buttonsLayout);
	

}

//function used for changing the state of the eventslist dedicated to the user
void UserGUI::populateRepoList()
{
	this->eventsListWidget->clear();

	vector<Event>allEvents = this->service.getElemsRepo();
	for (Event& e : allEvents)
		this->eventsListWidget->addItem(QString::fromStdString(e.getTitle() + " " + e.getDescription() + " " + e.getDate().getDay() + "-" + e.getDate().getMonth() + "-" + e.getDate().getYear() + " " + e.getTime() + " " + to_string(e.getNrPeople()) + " " + e.getLink()));
}

//fuction used for populating the list of events chosen by the user
void UserGUI::populateList()
{
	this->eventsListsWidget->clear();

	vector<Event>allEvents = this->service.getElems();
	for (Event& e : allEvents)
		this->eventsListsWidget->addItem(QString::fromStdString(e.getTitle() + " " + e.getDescription() + " " + e.getDate().getDay() + "-" + e.getDate().getMonth() + "-" + e.getDate().getYear() + " " + e.getTime() + " " + to_string(e.getNrPeople()) + " " + e.getLink()));
	
    
}

//function used for making connections - user gui
void UserGUI::connectSignalandSlots()
{
	
	QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Event e = this->service.getElemsRepo()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(e.getTitle()));
		this->descriptionLineEdit->setText(QString::fromStdString(e.getDescription()));
		this->dateLineEdit->setText(QString::fromStdString(e.getDate().getDay()) + "-" + QString::fromStdString(e.getDate().getMonth()) + "-" + QString::fromStdString(e.getDate().getYear()));
		this->timeLineEdit->setText(QString::fromStdString(e.getTime()));
		this->nrPeopleLineEdit->setText(QString::fromStdString(to_string(e.getNrPeople())));
		this->linkLineEdit->setText(QString::fromStdString(e.getLink()));

		});
	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addEventList);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &UserGUI::deleteEventList);
	QObject::connect(this->openButton, &QPushButton::clicked, this, &UserGUI::openFile);
	QObject::connect(this->filterByMonthButton, &QPushButton::clicked, this,&UserGUI::filterMonth);
}

void UserGUI::openFile() {
	
	Date data = Date("12", "02", "2022");
	Event e = Event("event", "description", data, "time", 100, "link");
	this->service.open(e);

}

//function used for returning the selected index
int UserGUI::getSelectedIndex() const
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

int UserGUI::getSelectedIndexList() 
{
	QModelIndexList selectedIndexes = this->eventsListsWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;

}

void UserGUI::filterMonth()
{   
	string month = this->dateLineEdit->text().toStdString();
	std::vector<Event> events = this->service.eventsMonth(month);
	this->eventsListsWidget->clear();
	for (Event& e : events)
		this->eventsListsWidget->addItem(QString::fromStdString(e.getTitle() + " " + e.getDescription() + " " + e.getDate().getDay() + "-" + e.getDate().getMonth() + "-" + e.getDate().getYear() + " " + e.getTime() + " " + to_string(e.getNrPeople()) + " " + e.getLink()));

}




//function used for adding an event to the user list of events
void UserGUI::addEventList()
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
	string month = words[1];
	string year = words[2];
	Date data = Date(day, month, year);
	Event e = Event(title, description, data, time, stoi(nrPeople), eventLink);
	if (this->service.findEventList(e.getTitle(),e.getDescription()) == 1)
		{
		this->service.addEventList(e);
		}
	else
	{
		QMessageBox::critical(this, "Error", "The event was already added to your list!");
		return;
	}

	this->populateList();
	int lastElement = this->service.getElemsRepo().size() - 1;
	this->eventsListsWidget->setCurrentRow(lastElement);
}

void UserGUI::deleteEventList() {
	int index = this->getSelectedIndexList();
	if (index < 0)
	{
		QMessageBox::critical(this, "Error", "No event was selected");
		return;
	}
	this->service.removeEventList(this->service.getElems()[index].getTitle());
	this->populateList();
}

