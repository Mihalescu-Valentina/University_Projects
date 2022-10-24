#include "RetakePracticeOOP.h"
#include <QtWidgets/QApplication>
#include "ProgrammerRepo.h"
#include "TaskRepo.h"
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string filename = "Team.txt";
    ProgrammerRepo prepo(filename);
    filename = "Tasks.txt";
    TaskRepo trepo(filename);
    Service service(prepo, trepo);
    std::vector<Programmer> elems = service.getProgrammers();
    for (Programmer& elem : elems)
    {
        auto window = new TaskManager { service,elem };
        window->show();
    }
    service.testRemove();
    service.testUpdate();
    return QApplication::exec();
}
