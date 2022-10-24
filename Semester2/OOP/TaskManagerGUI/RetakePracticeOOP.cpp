#include "RetakePracticeOOP.h"
#include "qmessagebox.h"
TaskManager::TaskManager(Service& s,Programmer &p,QWidget *parent)
    : service{ s }, p{ p },QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateList();
	this->setWindowTitle((p.getName()).c_str());
	this->update();
	this->connectSignalsSlots();
	this->service.addObserver(this);
}

TaskManager::~TaskManager()
{}

void TaskManager::populateList()
{
	this->ui.listWidget->clear();

	for (auto elem : this->service.getsortedTasks()) {
		std::string str = elem.getDescription() + ", " + elem.getStatus();
		this->ui.listWidget->addItem(QString::fromStdString(str));
	}
}

void TaskManager::connectSignalsSlots()
{
	QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &TaskManager::addTask);
	QObject::connect(this->ui.deletePushButton, &QPushButton::clicked, this, &TaskManager::removeTask);
	QObject::connect(this->ui.startPushButton, &QPushButton::clicked, this, &TaskManager::changeSelected);
	
}

void TaskManager::update()
{
	this->populateList();
}

void TaskManager::addTask()
{
	
	
		std::string description = this->ui.addLineEdit->text().toStdString();
		if (description != " " && this->service.findTask(description) == 0) {
			this->service.addTask(description, this->p.getId());
			this->populateList();

		}
		else {
			MyException ex{"Add error,try again!"};
			QMessageBox::critical(this, "Error", ex.what());
			return;
		}
	




}

void TaskManager::removeTask()
{
	std::string description = this->ui.deleteLineEdit->text().toStdString();
	if (description != " " && this->service.findTask(description) == 1) {
		this->service.removeTask(description);
		this->populateList();
	}
	else
	{
		QMessageBox::critical(this, "Error", "The entity does not exist!");
		return;
	}

}

void TaskManager::changeSelected()
{
	int index = this->ui.listWidget->currentRow();
	Task current = this->service.getsortedTasks()[index];
	if (current.getStatus() == "open") {
		this->service.updateTask(index, current);
		this->service.getTasks()[index].setDescription(this->service.getTasks()[index].getDescription() + this->p.getName());
		this->populateUpdatedList();
	}

	else
	{
		QMessageBox::critical(this, "Error", "The task is NOT open!");
		return;
	}

}

void TaskManager::populateUpdatedList()
{
	this->ui.listWidget->clear();

	for (auto elem : this->service.getsortedTasks()) {
		std::string str = elem.getDescription() + ", " + elem.getStatus();
		if (elem.getStatus() == "in progress") {
			str += "," + this->p.getName();
		}
		this->ui.listWidget->addItem(QString::fromStdString(str));
	}
}
