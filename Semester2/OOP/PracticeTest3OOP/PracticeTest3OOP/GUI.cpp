#include "GUI.h"
#include<qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>

GUI::GUI(Service s) : s{s}
{
	this->initGUI();
	this->populateList();
	this->connectSignalandSlots();
}

void GUI::initGUI()
{
	this->tasksListWidget = new QListWidget();
	this->filteredListWidget = new QListWidget();
	this->priorityLineEdit = new QLineEdit();
	this->priorityButton = new QPushButton("Show by priority");
	//this->durationLineEdit = new QLineEdit();
	this->descriptionLineEdit = new QLineEdit();

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(this->tasksListWidget);
	mainLayout->addWidget(this->filteredListWidget);
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Priority that you want to filter by", this->priorityLineEdit);
	formLayout->addRow("Search", this->descriptionLineEdit);
	mainLayout->addLayout(formLayout);
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->addWidget(this->priorityButton, 0, 0);
	mainLayout->addLayout(buttonsLayout);

}

void GUI::populateList()
{
	this->tasksListWidget->clear();

	std::vector<Task>tasks = this->s.getElems();
	int i = 0;
	for (Task& elem : tasks)
	{
		this->tasksListWidget->addItem(QString::fromStdString(elem.getDescription() + " | " + std::to_string(elem.getDuration()) + " | " + std::to_string(elem.getPriority()) + "\n"));
		if (elem.getPriority() == 1)
		this->tasksListWidget->item(i)->setBackground(Qt::red);
		
		if (elem.getPriority() == 2)
		{
			//this->tasksListWidget->item(i)->setForeground(Qt::blue);
			QFont font = this->tasksListWidget->item(i)->font();
			font.setBold(true);
			font.setItalic(true);
			font.setUnderline(true);
			//font.setOverline(true);
			this->tasksListWidget->item(i)->setFont(font);
			
			
			
		}
		i++;
	}

}
/*
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
void Service::addEvent()
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
	if (this->service.findEventRepo(e.getTitle(), e.getDescription()) == 1)
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
		QMessageBox::critical(this, "Error", "No event was selected");
		return;
	}
	this->service.remove(this->service.getElemsRepo()[index].getTitle());
	this->populateRepoList();
}
*/

void GUI::connectSignalandSlots()
{
	QObject::connect(this->priorityButton, &QPushButton::clicked, this, &GUI::populateFilteredList);

}

void GUI::populateFilteredList() {

	int p = this->priorityLineEdit->text().toInt();
	this->filteredListWidget->clear();
	
	std::vector<Task>filtered = this->s.filterByPriority(p);
	if (filtered.size() == 0)
		QMessageBox::critical(this, "Error", "No priority was entered");
	for (Task elem : filtered)
		this->filteredListWidget->addItem(QString::fromStdString(elem.getDescription() + " | " + std::to_string(elem.getDuration()) + " | " + std::to_string(elem.getPriority()) + "\n"));
	
}

void search(std::string description)
{

}