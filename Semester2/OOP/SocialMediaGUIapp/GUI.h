#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Service.h"
#include "User.h"
#include "Observer.h"

class GUI : public QMainWindow,public Observer
{
    Q_OBJECT

public:
    GUI(Service& s, User& u,QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUIClass ui;
    Service& s;
    User& u;
    void populateFeedList();
    void populateTopicsList();
    void populatePostsList();
    void connectSignalsSlots();
    void update() override;
    void updatePost();
    void addPost();
    void subscribeToTopic();
};
