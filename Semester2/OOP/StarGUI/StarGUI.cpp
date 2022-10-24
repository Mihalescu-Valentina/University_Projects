#include "StarGUI.h"
#include "qmessagebox.h"
StarGUI::StarGUI(Service& _s,Astronomer& _a,AstronomersTableModel& model,Models& models,QWidget *parent)
	: service{ _s }, a{ _a }, model{ &model }, models{ models }, QMainWindow(parent)
{
    ui.setupUi(this);
	ui.tableView->setModel(this->model);
    this->setWindowTitle((a.getName()).c_str());
	this->populateList();
	this->connectSignalsSlots();
	
}

StarGUI::~StarGUI()
{}

void StarGUI::populateList()
{
	this->ui.listWidget->clear();

	for (auto elem : this->service.getsortedStars()) {
		std::string str = elem.getName() + ", " + elem.getConstellation()+","+std::to_string(elem.getRa())+","+std::to_string(elem.getDec())+","+std::to_string(elem.getDec());
		this->ui.listWidget->addItem(QString::fromStdString(str));
	}
}

void StarGUI::connectSignalsSlots()
{
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &StarGUI::addStar);
	//QObject::connect(this->ui.checkBox, &QCheckBox::released, this, &StarGUI::addStar);
	//QObject::connect(this->ui.checkBox, &QCheckBox::clicked, this, &StarGUI::addStar);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &StarGUI::updateStar);
}


void StarGUI::addStar()
{
	std::string name = this->ui.nameLineEdit->text().toStdString();
	int ra = this->ui.RaLineEdit->text().toInt();
	int dec = this->ui.decLineEdit->text().toInt();
	int diameter = this->ui.diameterLineEdit->text().toInt();
	if (name != " " && this->service.findStar(name) == 0) {
		this->service.addStar(Star(name, this->a.getConstellation(), ra, dec, diameter));
		this->populateList();
		for(auto model:this->models.getModels())
			model->changed();
	}


	else
	{
		QMessageBox::critical(this, "Error", "The entity was already added to your list!");
		return;
	}

}

void StarGUI::updateStar()
{
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string newname = this->ui.newNameLineEdit->text().toStdString();
	std::string constellation = this->ui.constellationLineEdit->text().toStdString();
	int ra = this->ui.RaLineEdit->text().toInt();
	int dec = this->ui.decLineEdit->text().toInt();
	int diameter = this->ui.diameterLineEdit->text().toInt();
	if (name != " " && this->service.findStar(name) == 1&&diameter>10) {
		this->service.updateStar(name,Star(newname, this->a.getConstellation(), ra, dec, diameter));
		this->populateList();
		for (auto model:this->models.getModels())
			model->changed();
	}
	else
	{
		QMessageBox::critical(this, "Error", "You cannot update,you did sth wrong");
		return;
	}
}





