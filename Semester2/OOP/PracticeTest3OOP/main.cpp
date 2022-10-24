#include "PracticeTest3OOP.h"
#include "Task.h"
#include "Service.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<Task> vect;
    vect.reserve(20);
    std::string filename = "tasks.txt";
    Service s = Service{ vect,filename };
    s.loadFromFile();
    GUI gui{ s };
    gui.show();
    return a.exec();
}
