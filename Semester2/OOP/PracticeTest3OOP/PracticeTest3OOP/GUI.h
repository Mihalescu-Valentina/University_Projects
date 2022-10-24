#pragma once
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include "Service.h"

class GUI : public QWidget
{
private:
	Service s;
	QListWidget* tasksListWidget,*filteredListWidget;
	QLineEdit* priorityLineEdit,*descriptionLineEdit;
	QPushButton* priorityButton;

public:
	explicit GUI(Service s);

private:
	void initGUI();
	void populateList();
	void connectSignalandSlots();
	void populateFilteredList();
	

};