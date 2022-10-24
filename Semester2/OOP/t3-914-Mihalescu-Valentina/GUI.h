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
	QListWidget* disordersListWidget, * filteredListWidget;
	QLineEdit* nameLineEdit, * symptomeLineEdit;
	QPushButton* symptomsButton,*refreshButton;

public:
	explicit GUI(Service s);

private:
	void initGUI();
	void populateList();
	void connectSignalandSlots();
	void populateFilteredList();

	void search();


};
