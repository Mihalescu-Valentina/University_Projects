#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QuestionsGUI.h"
#include "User.h"
#include "Service.h"

class QuestionsGUI : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    QuestionsGUI(Service& s,User& u,QWidget *parent = nullptr);
    ~QuestionsGUI();

private:
    Ui::QuestionsGUIClass ui;
    Service& s;
    User& u;
public:
    void populateList();
    void connectSignalsAndSlots();
    void update() override;
    void addQuestion();
    void populateList2();
    void addAnswer();
    void removeQuestion();
    int getSelectedIndex() const;
    int getSelectedIndex2() const;
    void SpinBox();
};
