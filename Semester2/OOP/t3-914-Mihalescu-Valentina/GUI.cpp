#include "GUI.h"
#include<qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>

GUI::GUI(Service s) : s{ s }
{
	this->initGUI();
	this->populateList();
	this->connectSignalandSlots();
}

void GUI::initGUI()
{
	this->disordersListWidget = new QListWidget();
	this->filteredListWidget = new QListWidget();
	this->nameLineEdit = new QLineEdit();
	this->symptomsButton = new QPushButton("Show symptoms");
	this->refreshButton = new QPushButton("Search button");
	this->symptomeLineEdit = new QLineEdit();

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(this->disordersListWidget);
	mainLayout->addWidget(this->filteredListWidget);
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Disorder that you want to filter by", this->nameLineEdit);
	formLayout->addRow("Search", this->symptomeLineEdit);
	mainLayout->addLayout(formLayout);
	QGridLayout* buttonsLayout = new QGridLayout();
	buttonsLayout->addWidget(this->symptomsButton, 0, 0);
	buttonsLayout->addWidget(this->refreshButton, 0, 1);
	mainLayout->addLayout(buttonsLayout);

}

void GUI::populateList()
{
	this->disordersListWidget->clear();

	std::vector<Disorder>tasks = this->s.getElems();
	for (Disorder& elem : tasks)
	{
		this->disordersListWidget->addItem(QString::fromStdString(elem.getCategory() + " | " + elem.getName() + "\n"));
		
	}

}


void GUI::connectSignalandSlots()
{
	QObject::connect(this->symptomsButton, &QPushButton::clicked, this, &GUI::populateFilteredList);
	QObject::connect(this->refreshButton, &QPushButton::clicked, this, &GUI::search);
}

void GUI::populateFilteredList() {

	std::string p = this->nameLineEdit->text().toStdString();
	this->filteredListWidget->clear();

	std::vector<Disorder>filtered = this->s.filterByDisorder(p);
	if (filtered.size() == 0)
		QMessageBox::critical(this, "Error", "No disorder was entered");
	for (Disorder elem : filtered)
		this->filteredListWidget->addItem(QString::fromStdString(elem.getSymptoms() + "\n"));

}

void GUI::search()
{   
	this->disordersListWidget->clear();
	std::string p = this->symptomeLineEdit->text().toStdString();
	std::vector<Disorder> elements = s.match(p);
	 for (Disorder elem : elements)
		this->disordersListWidget->addItem(QString::fromStdString(elem.getSymptoms() + "\n"));

}