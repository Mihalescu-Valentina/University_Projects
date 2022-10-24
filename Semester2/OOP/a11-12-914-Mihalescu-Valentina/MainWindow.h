#pragma once
#include <qwidget.h>
#include<qpushbutton.h>
#include <qgridlayout.h>
#include<qdialog.h>
class MainWindow :
    public QDialog

{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    QGridLayout* mainWindowButtonsLayout;
    QPushButton* htmlButton, * csvButton;

public:

    explicit MainWindow(QWidget* parent = 0);

private:

    void initGui();
    void connect_signals_and_slots();
    void runCsv();
    void runHtml();

};

