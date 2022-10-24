#include "MainWindow.h"
#include "AdministratorGUI.h"
#include"Service.h"
#include "Repository.h"
#include "AdministratorUser.h"
#include<memory>

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QDialog(parent)
{
	this->initGui();
	this->connect_signals_and_slots();
	
}

//function used for initialising the gui where the user gets to choose between csv and html
void MainWindow::initGui()
{
	this->mainLayout = new QVBoxLayout(this);
	this->mainWindowButtonsLayout = new QGridLayout();
	this->csvButton = new QPushButton("Csv");
	this->htmlButton = new QPushButton("Html");
	this->mainWindowButtonsLayout->addWidget(this->csvButton, 0, 0);
	this->mainWindowButtonsLayout->addWidget(this->htmlButton, 0, 1);
	this->mainLayout->addLayout(mainWindowButtonsLayout);

}

//function for making connections
void MainWindow::connect_signals_and_slots()
{
	QObject::connect(this->csvButton, &QPushButton::clicked, this, &MainWindow::runCsv);
	QObject::connect(this->htmlButton, &QPushButton::clicked, this, &MainWindow::runHtml);
} 

//function for running the programme using csv output file
void MainWindow::runCsv()
{
	
	unique_ptr<Repository_file> repo = make_unique<Repository_file>();
	unique_ptr<EventsList> events_csv = make_unique<EventsListCsv>();
	Service service(repo.get(), events_csv.get());
	service.read();
	AdministratorUser gui{service};
	gui.exec();
	
}

//function used for running the programme using html output file
void MainWindow::runHtml()
{
	unique_ptr<Repository_file> repo = make_unique<Repository_file>();
	unique_ptr<EventsList> events_html = make_unique<EventsListHtml>();
	Service service(repo.get(), events_html.get());
	service.read();
	AdministratorUser gui{ service };
	gui.exec();
}
