#include "QuestionsGUI.h"
#include <qmessagebox.h>

QuestionsGUI::QuestionsGUI(Service& s,User& u,QWidget *parent)
    : s{ s }, u{ u },QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateList();
	this->populateList2();
	this->setWindowTitle((u.getName()).c_str());
	this->update();
	this->connectSignalsAndSlots();
	this->s.addObserver(this);
	this->SpinBox();
}

QuestionsGUI::~QuestionsGUI()
{}

void QuestionsGUI::populateList()
{
	this->ui.listWidget->clear();
	std::vector<Question> sortedQuestions = this->s.getSortedQuestions();
	for (auto elem : sortedQuestions) {
		std::string str = std::to_string(elem.getId()) + ", " + elem.getDescription()+", "+elem.getName();
		this->ui.listWidget->addItem(QString::fromStdString(str));
	}
}

void QuestionsGUI::populateList2() {

	this->ui.listWidget2->clear();
	int index = this->getSelectedIndex();
	if (index != -1) {
		std::vector<Answer> answers = this->s.showAnswers(this->s.getSortedQuestions()[index]);
		for (auto elem : answers) {
			std::string str = std::to_string(elem.getAnswerId()) + ", " + std::to_string(elem.getQuestionId()) + ", " + elem.getName() + "," + elem.getText() + "," + std::to_string(elem.getNrVotes());
			this->ui.listWidget2->addItem(QString::fromStdString(str));

		}

	}

}


void QuestionsGUI::connectSignalsAndSlots()
{
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &QuestionsGUI::addQuestion);
	QObject::connect(this->ui.listWidget, &QListWidget::itemSelectionChanged, this, &QuestionsGUI::populateList2);
	QObject::connect(this->ui.answerButton, &QPushButton::clicked, this, &QuestionsGUI::addAnswer);
	QObject::connect(this->ui.removeButton, &QPushButton::clicked, this, &QuestionsGUI::removeQuestion);
	QObject::connect(this->ui.spinBox, &QSpinBox::valueChanged, this, &QuestionsGUI::SpinBox);
}

void QuestionsGUI::update()
{
	this->populateList();
	this->populateList2();
}

void QuestionsGUI::addQuestion()
{
	std::string description = this->ui.nameLineEdit->text().toStdString();
	int id = this->ui.idLineEdit->text().toInt();
	if (description != "" && this->s.findQuestion(description) == 0) {
		this->s.addQuestion(id,description,this->u.getName());
		this->populateList();

	}
	else
	{
		QMessageBox::critical(this, "Error", "The entity was already added to your list!");
		return;
	}
}


void QuestionsGUI::addAnswer() {

    std::string name= this->ui.answerLineEdit->text().toStdString();
	int questionId = this->ui.questionLineEdit->text().toInt();
	int id = 1 + (rand() % 100);
	this->s.addAnswer(Answer(id,questionId,this->u.getName(), name, 0));
	
}

void QuestionsGUI::removeQuestion()
{
	std::string description = this->ui.nameLineEdit->text().toStdString();
	int id = this->ui.idLineEdit->text().toInt();
	if (description != "" && this->s.findQuestion(description) == 1) {
		this->s.removeQuestion(description);
		this->populateList();

	}
	else
	{
		QMessageBox::critical(this, "Error", "The entity was already added to your list!");
		return;
	}
}



int QuestionsGUI::getSelectedIndex() const
{   
	
	QModelIndexList selectedIndexes = this->ui.listWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;

}


int QuestionsGUI::getSelectedIndex2() const
{

	QModelIndexList selectedIndexes = this->ui.listWidget2->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{

		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;

}

void QuestionsGUI::SpinBox() {
	int answerId = this->ui.answerLineEdit->text().toInt();
	for (auto elem : this->s.getAnswers())
		if (elem.getAnswerId() == answerId && elem.getName() != this->u.getName()) {
			int value = this->ui.spinBox->value();
			elem.setNrVotes(value);
			return;
		}
		else
			this->ui.spinBox->disconnect();
			
	

}