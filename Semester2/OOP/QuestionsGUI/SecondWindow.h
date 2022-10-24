#pragma once
#include <QObject>
#include <qpushbutton.h>
#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <qlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdialog.h>
#include "Service.h"
class SecondWindow  : public QDialog
{
	Q_OBJECT

public:
	SecondWindow(const char* name,Service&s, QWidget* parent = 0);
	~SecondWindow();
	void init();
	void connectSignalsAndSlots();
	void showSearch();
	void populateList();
private:
	QPushButton* searchButton;
	QLineEdit* searchLineEdit;
	QVBoxLayout* mainLayout;
	QListWidget* listWidget;
	Service& s;
};
