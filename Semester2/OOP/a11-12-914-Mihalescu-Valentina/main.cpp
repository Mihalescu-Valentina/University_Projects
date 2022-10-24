#include "HomeWork1112QtGUI.h"
#include <QtWidgets/QApplication>
#include"Service.h"
#include "Repository.h"
#include<iostream>
#include"UI.h"
#include<memory>
#include "MainWindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cout << "What tipe of file would you like to use? csv or html?";
    int ok = 1;
    char ch[20];
    MainWindow gui;
    gui.show();
    return a.exec();
    
}
