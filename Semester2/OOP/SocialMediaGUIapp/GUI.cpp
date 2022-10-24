#include "GUI.h"
#include <qmessagebox.h>
GUI::GUI(Service& s, User& u, QWidget *parent)
    : s{ s }, u{ u }, QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateFeedList();
	this->populatePostsList();
	this->populateTopicsList();
	this->setWindowTitle((u.getName()).c_str());
	this->connectSignalsSlots();
    this->update();
    this->s.addObserver(this);
}

GUI::~GUI()
{}


void GUI::populateFeedList()
{
	this->ui.feedListWidget->clear();

	for (int i = 0; i < this->s.getPosts().size(); i++) {
		
			std::string str = std::to_string(this->s.getPosts()[i].getId()) + "," + this->s.getPosts()[i].getText() + "," + this->s.getPosts()[i].getTime() + "," + this->s.getPosts()[i].getUser();
			this->ui.feedListWidget->addItem(QString::fromStdString(str));
			if (this->s.getPosts()[i].getUser()[0] == '@') {
				this->ui.feedListWidget->item(i)->setBackground(Qt::blue);
			}
			
		
	}
}

void GUI::populateTopicsList() {
	this->ui.topicListWidget->clear();

	for (auto elem : this->s.getTopics()) {
		std::size_t found = elem.getSubscribers().find(this->u.getName());
		if (found != std::string::npos) {
			std::string str = elem.getTopic() + "," + elem.getSubscribers();
			this->ui.topicListWidget->addItem(QString::fromStdString(str));
		}
		std::string str = elem.getTopic() + "," + elem.getSubscribers();
		this->ui.topicListWidget->addItem(QString::fromStdString(str));
		
	}
}

void GUI::populatePostsList() {
	this->ui.postsListWidget->clear();

	for (auto elem : this->s.getPosts()) {
		std::string str = std::to_string(elem.getId()) + "," + elem.getText() + "," + elem.getTime() + "," + elem.getUser();
		this->ui.postsListWidget->addItem(QString::fromStdString(str));
	}

}


void GUI::connectSignalsSlots() {
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &GUI::updatePost);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &GUI::addPost);
	QObject::connect(this->ui.subscribeButton, &QPushButton::clicked, this, &GUI::subscribeToTopic);
}

void GUI::update()
{
    this->populateFeedList();
	this->populatePostsList();
	this->populateTopicsList();
}

void GUI::updatePost() {

	std::string oldtext = this->ui.oldLineEdit->text().toStdString();
	std::string newtext = this->ui.newLineEdit->text().toStdString();
	for (auto elem : this->s.getPosts()) {
		this->s.updatePost(oldtext, newtext);
		this->populatePostsList();
	}

}

void GUI::addPost() {
	std::string text = this->ui.textLineEdit->text().toStdString();
	std::string time = this->ui.timeLineEdit->text().toStdString();
	std::string user = this->ui.userLineEdit->text().toStdString();
	int id = this->ui.idLineEdit->text().toInt();
	
	if (text.size() >= 3)
	{
		this->s.addPost(id, text, time, user);
		this->populatePostsList();
	}
	else
	{
	QMessageBox::critical(this, "Error", "The entity name must have at leats 3 characters!");
	return;
	}
	
}

void GUI::subscribeToTopic() {
	std::string topic = this->ui.subscribeLineEdit->text().toStdString();
	for (auto elem : this->s.getTopics())
		if (elem.getTopic() == topic) {
			std::string str = elem.getTopic() + ";" + topic;
			elem.setTopic(str);
			this->s.writeToFile();
		}
	

}