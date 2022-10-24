/*#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}*/

#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "UserRepo.h"
#include "TopicRepo.h"
#include "PostRepo.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    std::string filename = "Users.txt";
    UserRepo urepo(filename);
    filename = "Topics.txt";
    TopicRepo trepo(filename);
    filename = "Posts.txt";
    PostRepo prepo(filename);
    Service service(urepo, trepo, prepo);
    std::vector<User> elems = service.getUsers();
    for (User& elem : elems)
    {
        auto window = new GUI{ service,elem };
        window->show();
    }
   
    return QApplication::exec();
}

